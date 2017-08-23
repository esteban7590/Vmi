/*
  Gprs.cpp - Library for http requests with Quectel M95.
  Created by Esteban Rojas, August 08 2017.
*/

//#include "Arduino.h"
#include "Gprs.h"

Gprs::Gprs(int pwrpin, int statuspin, int srxpin, int stxpin){
  pinMode(pwrpin, OUTPUT);
  _pwrpin = pwrpin;

  pinMode(statuspin, INPUT);
  _statuspin = statuspin;

  // if ((digitalRead(statuspin)) == LOW) {
  //   digitalWrite(pwrpin, HIGH);
  //
  //     while ((digitalRead(statuspin)) == LOW) {
  //       delay(200);
  //       }
  //
  // digitalWrite(pwrpin, LOW);
  // }
  SoftwareSerial gprs(srxpin ,stxpin);
  gprs.begin(9600);

  _srxpin = srxpin;
  _stxpin = stxpin;
}

void Gprs::config(String type, String device, String variable, String token){

  _type = type;
  _device = device;
  _variable = variable;
  _token = token;

  Serial.begin(9600);
  SoftwareSerial gprs(_srxpin, _stxpin);
  gprs.begin(9600);

  gprs.println("ATE0");
  Serial.print("Echo-off");
  delay(100);
  gprs.read();
  while(gprs.available()){
    Serial.print(char(gprs.read()));
  }
  Serial.println("---");

  gprs.print("AT+QISRVC=1\r");
  Serial.print("Connection Type 1");
  delay(100);
  gprs.read();
  while(gprs.available()){
    Serial.print(char(gprs.read()));
  }
  Serial.println("---");
}

void Gprs::set_apn(String apn){
  Serial.begin(9600);
  SoftwareSerial gprs(_srxpin, _stxpin);
  gprs.begin(9600);

  _apn = apn;

  gprs.println("AT+QICSGP=1," +  _apn);
  Serial.print("APN");
  delay(100);
  gprs.read();
  while (gprs.available()) {
    Serial.print(char(gprs.read()));
  }
  Serial.println("---");
  _apn = apn;
}

void Gprs::send(String ip, String port, int content){

  Serial.begin(9600);

  _ip = ip;
  _port = port;

  SoftwareSerial gprs(_srxpin, _stxpin);
  gprs.begin(9600);

  Serial.println("Open TCP/IP");
  gprs.print("AT+QIOPEN=\"TCP\",\""+ _ip + "\"," + _port +"\r");
  delay(5000);
  while (gprs.available()) {
    Serial.print(char(gprs.read()));
  }
  Serial.println("---");

  Serial.println("Send Data");
  gprs.print("AT+QISEND\r");//
  delay(1000);
  while (gprs.available()) {
    Serial.print(char(gprs.read()));
  }
  Serial.println("---");

  StaticJsonBuffer<200> jsonBuffer;
  //int x = 900;
   String inp1 = "{\"value\":";
   //String y = String(x);
   String inp3 = "}";

   String inp = inp1 + content + inp3;
   //String inp = Serial.readStringUntil('\n');
  JsonObject& req = jsonBuffer.parseObject(inp);

  String output;
  req.printTo(output);

  Serial.println("Write Data");
  gprs.print("POST /api/v1.6/devices/");
  gprs.print(_device);gprs.print("/");gprs.print(_variable);gprs.print("/");
  gprs.print("values?token");
  gprs.print(_token);gprs.println(" HTTP/1.1");
  gprs.println("Host: things.ubidots.com");
  gprs.print("Content-Type: ");gprs.println(_type);
  gprs.print("Content-Length: ");gprs.println(output.length());
  gprs.println("");
  gprs.println(output);
  gprs.write(0x1A);
  delay(1000);
  while (gprs.available()) {
    Serial.print(char(gprs.read()));
  }
  Serial.println("---");
  Serial.println("Waiting for response");
  delay(5000);
  while (gprs.available()) {
    Serial.print(char(gprs.read()));
    gprs.print("");
  }
}

void Gprs::close(){
  Serial.begin(9600);

  SoftwareSerial gprs(_srxpin, _stxpin);
  gprs.begin(9600);

  Serial.println("Close TCP/IP");
  gprs.print("AT+QCLOSE\r");
  delay(100);
  while (gprs.available()) {
    Serial.print(char(gprs.read()));
  }
  Serial.println("---");
}
