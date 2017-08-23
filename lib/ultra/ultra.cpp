
#include "ultra.h"

ultra::ultra(int trigger, int echo)
{
   pinMode(trigger, OUTPUT);
   _trigger = trigger;

   pinMode(echo, INPUT);
   _echo = echo;
}

int ultra::medir()
{

    Serial.begin (9600);

    digitalWrite(_trigger,LOW); /* Por cuestion de estabilizacion del sensor*/
    delayMicroseconds(2);

    digitalWrite(_trigger, HIGH); /* envoo del pulso ultrasonico*/
    delayMicroseconds(10);

    digitalWrite(_trigger, LOW);

    long tiempo_vuelo=pulseIn(_echo, HIGH);
    _distancia = (tiempo_vuelo/2) / 29.1;

    delay(5);

    Serial.print("distancia ");
    Serial.println(_distancia);
    delay(5);

    return _distancia;

   }
