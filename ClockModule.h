#ifndef ClockModule_h
#define ClockModule_h

#include "Wire.h"
#include "DS3231.h"
#include "WiFiUdp.h"
#include "Arduino.h"
#include "TimeLib.h"
#include "GlobalProperties.h"

class ClockModule {
  public:
    ClockModule(); 
    void Setup();
    void setClockModule();
  private:
    int localPort = 2390;
    int timeCheckLoop;
    static const int NTP_PACKET_SIZE = 48;    // NTP time stamp is in the first 48 bytes of the message
    byte packetBuffer[ NTP_PACKET_SIZE];      //buffer to hold incoming and outgoing packets
    IPAddress timeServer; // time.nist.gov NTP server
    unsigned long epoch;
    unsigned long LastNTP;
    WiFiUDP udp;
    DS3231 Clock;
    bool h12;
    bool PM;
    void requestTime();
    unsigned long sendNTPpacket (IPAddress & address);
    bool checkTime();
    bool isDST(int days, int months, int dow, int hours);
    void setRTC();
};

#endif
