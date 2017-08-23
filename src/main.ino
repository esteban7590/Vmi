#include <Estibas.h>

#define echo 3 // echo pin
#define trigger 4 // trigger pin
#define distancia_piso 240 // cm

#define alt_estiba 130 // cm
#define tolerance 5 // % of alt estiba

Estibas columna(echo, trigger, distancia_piso);

#include <Gprs.h>

Gprs celular(7,8,2,3); //pwrpin, statuspin, rx, tx

#include <Reloj.h>

Reloj time;

void setup(){

  time.set_time();
  time.printDateTime();
  time.set_alarm(8,15); //hour, minute

  celular.config("application/json", "vmi", "capas", "zjLwMAMo3TzwgFqZ6vL2rCHmvPMhjl"); //content type, device, variable, token
  celular.set_apn("\"internet.movistar.com.co\""); //"apn"
}

void loop(){

int value = columna.cantidad_filtered(tolerance, alt_estiba);

celular.send("50.23.124.68", "80", value);  //ip, port, content-type, value
celular.close();

int hour = time.get_time_hours();

if (hour == 8){
  time.set_alarm(12,15); //hour, minutes
}

if (hour == 12){
  time.set_alarm(18,15); //hour, minutes
}

if (hour == 18){
  time.set_alarm(8,15); //hour, minutes
}

delay(5000);

time.reset_alarm();

}
