#ifndef ADS1115_WE_H
#define ADS1115_WE_H

#include <Arduino.h>
typedef enum ADS1115_MUX{
    ADS1115_COMP_0_1   = 0,
    ADS1115_COMP_0_3   = 1,
    ADS1115_COMP_1_3   = 2,
    ADS1115_COMP_2_3   = 3,
    ADS1115_COMP_0_GND = 4,
    ADS1115_COMP_1_GND = 5,
    ADS1115_COMP_2_GND = 6,
    ADS1115_COMP_3_GND = 7,
    ADS1015_COMP_0_1   = ADS1115_COMP_0_1,
    ADS1015_COMP_0_3   = ADS1115_COMP_0_3,
    ADS1015_COMP_1_3   = ADS1115_COMP_1_3,
    ADS1015_COMP_2_3   = ADS1115_COMP_2_3,
    ADS1015_COMP_0_GND = ADS1115_COMP_0_GND,
    ADS1015_COMP_1_GND = ADS1115_COMP_1_GND,
    ADS1015_COMP_2_GND = ADS1115_COMP_2_GND,
    ADS1015_COMP_3_GND = ADS1115_COMP_3_GND 
} mux;



class ADS1115_WE
{
    public:


        ADS1115_WE(const unsigned int addr = 0x48) {};


        void reset();
        bool init(bool ads1015 = false);

};


#endif //ADS1115_WE_H