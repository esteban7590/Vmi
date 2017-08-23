/*
Estibas.h - Library for measuring estibas and send data to http.
Created by Esteban Rojas, 22 August 2018.
*/

#ifndef Estibas_h
#define Estibas_h

#include "Arduino.h"
#include "ultra.h"
#include "Array.h"

class Estibas
{
  public:
    Estibas(int echo, int trigger, int dist_piso);
    int cantidad(int tolerancia, int alto_estiba);
    int cantidad_filtered(int tolerancia, int alto_estiba);

  private:
    int _dist_piso;
    int _estibas;
    int _tolerancia;
    int _alto_estiba;
    int _echo;
    int _trigger;
    int _filtrado;
};

#endif
