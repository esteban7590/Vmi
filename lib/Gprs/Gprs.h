/*
  Gprs.h - Library for http requests with Quectel M95.
  Created by Esteban Rojas, August 2017.
*/
#ifndef Gprs_h
#define Gprs_h

#include "Arduino.h"
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

class Gprs
{
  public:
    Gprs(int, int, int, int);
    void config(String type, String device, String variable, String token);
    void set_apn(String apn);
    void send(String ip, String port, int content);
    void close();

  private:
    int _pwrpin;
    int _statuspin;
    int _srxpin;
    int _stxpin;
    String _apn;
    String _port;
    String _ip;
    String _type;
    String _device;
    String _variable;
    String _token;
    int _content;

};

#endif
