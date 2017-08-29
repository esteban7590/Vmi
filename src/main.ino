#include <Estibas.h>

#define echo 2 // echo pin
#define trigger 0 // trigger pin
#define distancia_piso 240 // cm

#define alt_estiba 130 // cm
#define tolerance 5 // % of alt estiba

Estibas columna(echo, trigger, distancia_piso);

#include <Gprs.h>

Gprs celular(14,12,3,1); //pwrpin, statuspin, rx, tx

#include <Reloj.h>

Reloj time;

void setup(){

  time.set_time();
  time.printDateTime();
  time.set_alarm(12,25); //hour, minute

  celular.config("application/json", "vmi", "capas", "zjLwMAMo3TzwgFqZ6vL2rCHmvPMhjl"); //content type, device, variable, token
  celular.set_apn("\"internet.movistar.com.co\""); //"apn"
}

void loop(){

int value = columna.cantidad_filtered(tolerance, alt_estiba);

celular.send("50.23.124.68", "80", value);  //ip, port, content-type, value
celular.close();

int hour = time.get_time_hours();
int minutes = time.get_time_minutes();

if (hour == 9 && minutes == 12){
  time.set_alarm(9,14); //hour, minutes
  time.reset_alarm();
}

if (hour == 9 && minutes == 14){
  time.set_alarm(9,16); //hour, minutes
  time.reset_alarm();
}

if (hour == 9 && minutes == 16){
  time.set_alarm(9,18); //hour, minutes
  time.reset_alarm();
}
time.reset_alarm();
}
