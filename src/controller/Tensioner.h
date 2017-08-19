#ifndef Tensioner_h
#define Tensioner_h

#include "HX711.h"

#define SPOOLL 'L' 
#define SPOOLR 'R'
class Tensioner {
    public:
        Tensioner(int sck, int dout, int enable, int outl, int outr);
        void select(char which); 
        float setpointL,setpointR;
        float offset,offsetR;
        float scaleL,scaleR;
        float tension;
        void begin();
        void loop();
    private:
        int pinSCK;
        int pinDOUT;
        int pinENABLE;
        int pinOUTL;
        int pinOUTR;
        char selection;
};

#endif
