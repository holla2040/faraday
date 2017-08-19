#include "Arduino.h"
#include "Tensioner.h"
#include "HX711.h"

HX711 loadcell;

Tensioner::Tensioner(int sck, int dout, int enable, int outl, int outr) {
    pinSCK      = sck;
    pinDOUT     = dout;
    pinENABLE   = enable;
    pinOUTL     = outl;
    pinOUTR     = outr;

    pinMode(pinSCK,OUTPUT);
    pinMode(pinDOUT,OUTPUT);
    pinMode(pinENABLE,INPUT);
    pinMode(pinOUTL,OUTPUT);
    pinMode(pinOUTR,OUTPUT);
    
    selection = SPOOLL;
}

void Tensioner::begin() {
    loadcell.begin(pinDOUT,pinSCK);
    loadcell.set_gain(32);
    loadcell.set_scale(2280.f);
    loadcell.tare();
}

void Tensioner::select(char which) {
    selection = which;
}    

void Tensioner::loop() {
    tension = loadcell.get_units(1);
}

