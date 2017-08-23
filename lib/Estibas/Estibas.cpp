/*
Estibas.cpp - Library for measuring estibas and send data to http.
Created by Esteban Rojas, 22 August 2018.
*/

#include "Estibas.h"

Estibas::Estibas(int echo, int trigger, int dist_piso){
_echo = echo;
_trigger = trigger;
_dist_piso = dist_piso;
}

int Estibas::cantidad(int tolerancia, int alto_estiba){

Serial.begin(9600);
delay(500);

ultra ultrasonic(_echo, _trigger);

_tolerancia = tolerancia;
_alto_estiba = alto_estiba;

int margen = _alto_estiba * _tolerancia;

int dist = ultrasonic.medir();
int cantidad = (dist - _dist_piso)/130;

if(cantidad < (margen)){
  _estibas = 0;
}

if(cantidad < (1 + margen) && cantidad > (1 - margen)){
  _estibas = 1;
}

if(cantidad < (2 + margen) && cantidad > (2 - margen)){
  _estibas = 2;
}

if(cantidad < (3 + margen) && cantidad > (3 - margen)){
  _estibas = 3;
}

if(cantidad > (3 + margen) || cantidad < 0){
  _estibas = 99;
}

return _estibas;
}

int Estibas::cantidad_filtered(int tolerancia, int alto_estiba){

  Serial.begin(9600);
  delay(500);

  ultra ultrasonic(_echo, _trigger);

  _tolerancia = tolerancia;
  _alto_estiba = alto_estiba;

  int primero,segundo,tercero,cuarto,quinto,sexto,septimo,octavo,noveno,decimo;

  for (int i=0; i<10; i++){

    int dist = ultrasonic.medir();
      if(i==0){
      primero = dist;
      }

      if(i==1){
      segundo = dist;
      }

      if(i==2){
      tercero = dist;
      }

      if(i==3){
      cuarto = dist;
      }

      if(i==4){
      quinto = dist;
      }

      if(i==5){
      sexto = dist;
      }

      if(i==6){
      septimo = dist;
      }

      if(i==7){
      octavo = dist;
      }

      if(i==8){
      noveno = dist;
      }

      if(i==9){
      decimo = dist;
      }
    }

  int rawArray[10] = {primero,segundo,tercero,cuarto,quinto,sexto,
                      septimo,octavo,noveno,decimo};
                      
  Array<int> array = Array<int>(rawArray,10);

  int sum = primero + segundo + tercero + cuarto + quinto + sexto
            + septimo + octavo + noveno + decimo;

  int avg = (sum - array.getMax() - array.getMin())/10;

  int cant_filt = (avg - _dist_piso)/130;

  int margen = _alto_estiba * _tolerancia;

  if(cant_filt < (margen)){
    _estibas = 0;
  }

  if(cant_filt < (1 + margen) && cant_filt > (1 - margen)){
    _estibas = 1;
  }

  if(cant_filt < (2 + margen) && cant_filt > (2 - margen)){
    _estibas = 2;
  }

  if(cant_filt < (3 + margen) && cant_filt > (3 - margen)){
    _estibas = 3;
  }

  if(cant_filt > (3 + margen) || cant_filt < 0){
    _estibas = 99;
  }

  	_filtrado = _estibas;

return _filtrado;
}
