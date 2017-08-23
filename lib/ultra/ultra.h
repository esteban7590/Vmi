#ifndef ultra_h
#define ultra_h

#include "Arduino.h"

class ultra {

public:
ultra (int trigger, int echo);
int medir ();

private:
int _trigger;
int _echo;
int _distancia;

};
#endif
