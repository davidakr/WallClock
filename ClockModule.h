#ifndef ClockModule_h
#define ClockeModule_h

#include "Wire.h"
#include "DS3231.h"
#include "WiFiUdp.h"
#include "Arduino.h"
#include "TimeLib.h"

class ClockModule {
public:
  int hour_ntp = 0;
  int minute_ntp = 0;
  int second_ntp = 0;
  String hourstr;
  String minstr;
  String secondstr;
  String yearstr;
  String monthstr;
  String daystr;
  int timezone = 1;
  int timeCheckLoop;
  int localPort = 2390;
  static const int NTP_PACKET_SIZE = 48;    // NTP time stamp is in the first 48 bytes of the message
  byte packetBuffer[ NTP_PACKET_SIZE];      //buffer to hold incoming and outgoing packets
  unsigned long epoch = 0;
  unsigned long LastNTP = 0;
  WiFiUDP udp;
  DS3231 Clock;
  bool h12;
  bool PM;
  void Setup();
  void requestTime();
  unsigned long sendNTPpacket (IPAddress & address);
  bool checkTime();
  bool isDST(int days, int months, int dow, int hours);
  void setRTC();
  void setClockModule();
};

#endif
