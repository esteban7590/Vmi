/*
Reloj.h - Library for setting time and alarm.
Created by Esteban Rojas, 16 August 2018.
*/

#ifndef Reloj_h
#define Reloj_h

#if defined(ESP8266)
#include <pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif

#include "Arduino.h"
#include <Wire.h>
#include <RtcDS3231.h>

#define countof(a) (sizeof(a) / sizeof(a[0]))

class Reloj
{
  public:
    // Reloj();
    void set_time();
    int get_time_hours();
    void set_alarm(int hour, int minutes);
    void reset_alarm();
    void printDateTime();
  private:
    int _hour;
    int _minutes;
};

#endif
