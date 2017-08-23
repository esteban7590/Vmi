/*
  Reloj.cpp - Library for setting time and alarm.
  Created by Esteban Rojas, 16 August 2018.
*/

#include "Reloj.h"

RtcDS3231<TwoWire> Rtc(Wire);

// Reloj::Reloj(){
//
// }

void Reloj::set_time(){

    Serial.begin(9600);
    delay(500);

    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

  if (!Rtc.IsDateTimeValid())
  {
      Serial.println("RTC lost confidence in the DateTime!");
      Rtc.SetDateTime(compiled);
  }

  if (!Rtc.GetIsRunning())
  {
      Serial.println("RTC was not actively running, starting now");
      Rtc.SetIsRunning(true);
  }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled)
  {
      Serial.println("RTC is older than compile time!  (Updating DateTime)");
      Rtc.SetDateTime(compiled);
  }
  Serial.println("set time");
}

int Reloj::get_time_hours(){

  Serial.begin(9600);
  delay(500);

  Rtc.Begin();

  RtcDateTime gt = Rtc.GetDateTime();

  int hours = gt.Hour();
  Serial.println(hours);

  return hours;
}

void Reloj::set_alarm(int hour, int minutes){
  Serial.begin(9600);
  delay(500);

  Rtc.Begin();

  Rtc.LatchAlarmsTriggeredFlags();

  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeAlarmOne);

  _hour = hour;
  _minutes = minutes;

  RtcDateTime alarmTime = RtcDateTime(000,00,00,_hour,_minutes,00);
  DS3231AlarmOne alarm1(
          alarmTime.Day(),
          alarmTime.Hour(),
          alarmTime.Minute(),
          alarmTime.Second(),
          DS3231AlarmOneControl_HoursMinutesSecondsMatch);
  Rtc.SetAlarmOne(alarm1);

  Serial.println("set alarm");
}

void Reloj::reset_alarm(){
  Rtc.Begin();
  Serial.begin(9600);
  delay(500);

  Rtc.LatchAlarmsTriggeredFlags();
  Serial.println("reset alarm");
}

void Reloj::printDateTime()
{
  Rtc.Begin();
  RtcDateTime dt = Rtc.GetDateTime();

  char datestring[20];

  snprintf_P(datestring,
      countof(datestring),
      PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
      dt.Month(),
      dt.Day(),
      dt.Year(),
      dt.Hour(),
      dt.Minute(),
      dt.Second() );
    Serial.println(datestring);
}
