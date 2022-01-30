#include "ClockModule.h"

ClockModule::ClockModule(): timeServer(129, 6, 15, 28) {
}

void ClockModule::Setup() {
  Wire.begin();
  //RTC Setup  false = 24h, true = 12h
  Clock.setClockMode(false);

  Serial.println("Starting UDP");
  udp.begin(localPort);
  //Serial.print("Local port: ");
  //Serial.println(udp.localPort());
}

void ClockModule::requestTime() {
  Serial.println("Getting Time");
  sendNTPpacket(timeServer); // send an NTP packet to a time server
}

unsigned long ClockModule::sendNTPpacket(IPAddress & address) {
  Serial.println("sending NTP packet...");
  //buffer to hold incoming and outgoing packets
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

bool ClockModule::checkTime() {
  int cb = udp.parsePacket();
  if (!cb) {
    Serial.println("no packet yet");
    return false;
  }
  else {
    Serial.print("packet received, length=");
    Serial.println(cb);
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, extract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;

    // now convert NTP time into everyday time:
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    epoch = secsSince1900 - seventyYears;
    LastNTP = millis();
    timeCheckLoop = 0;
    Serial.print("epoch = ");
    Serial.println(epoch);

    //Update for timezone
    String hourstr = String(hour(epoch) + TIMEZONE);
    String minstr = String(minute(epoch));
    String secondstr = String(second(epoch));
    String yearstr = String(year(epoch));
    String monthstr = String(month(epoch));
    String daystr = String(day(epoch));
    Serial.print("Unix time = ");
    Serial.println(hourstr + ":" + minstr + ":" + secondstr + ", " + daystr + "." + monthstr + "." + yearstr );

    //Set RTC
    setRTC();

    return true;
  }
}

bool ClockModule::isDST(int days, int months, int dow, int hours) {
  boolean pm = false;
  if (hours > 12) {                                 // 12h am/pm
    hours -= 12;
    pm = true;
  }

  if (months <= 2 || months >= 11)
    return false;                                   // Winter months
  if (months >= 4 && months <= 9)
    return true;                                    // Summer months
  /***  Detect the beginning of the DST in March ***/
  if (months == 3 && (days - dow >= 25)) {            // Begin of summer time
    if (pm == false && hours >= 3 - 1 || pm == true) {
      return true;                                  // MESZ – 1 hour
    } else {
      return false;
    }
  } else {
    return false;
  }
  // Still summer months time DST beginning of October
  if (months == 10 && days - dow < 25) {
    return true;                                    // Summer months anyway until 24th of October
  }

  //Test the begin of the winter time in October
  if (months == 10 && days - dow >= 25) {
    if (pm == false && hours >= 3 - 1 || pm == true) {
      return false;
    } else {
      return true;
    }
  }
}

void ClockModule::setRTC() {
  Clock.setSecond(second(epoch));
  Clock.setMinute(minute(epoch));
  Clock.setHour(hour(epoch) + TIMEZONE);

  Clock.setYear(year(epoch));
  Clock.setMonth(month(epoch));
  Clock.setDoW(weekday(epoch));

  //Check for DST
  if (isDST(day(epoch), month(epoch), weekday(epoch), hour(epoch) + TIMEZONE)) {
    Serial.println("We have summer time");
    Clock.setHour(Clock.getHour(h12, PM) + 1);
  } else {
    Serial.println("We have winter time");
  }
}

void ClockModule::getNTP() {
  requestTime();
  delay(500);
  while (!checkTime()) {
    delay(2000);
    timeCheckLoop++;
    if (timeCheckLoop > 5) {
      Serial.println("Will restart because no NTP package arrived");
      ESP.restart();
    }
  }
}

int ClockModule::getSeconds() {
  //ESP.wdtDisable();
  int currentSecond = Clock.getSecond();
  //ESP.wdtEnable(2000);
  return currentSecond;
}

int ClockModule::getMinutes() {
  //ESP.wdtDisable();
  int currentMinute = Clock.getMinute();
  //ESP.wdtEnable(2000);
  return currentMinute;
}

int ClockModule::getHours() {
  //ESP.wdtDisable();
  int currentHour = Clock.getHour(h12, PM);
  //ESP.wdtEnable(2000);
  return currentHour;
}
