// Copyright (C) 2024 Casey Gregoire <caseyg@lalosoft.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
// SOFTWARE.

#ifndef ADS1115_WE_H
#define ADS1115_WE_H

#include <Arduino.h>
typedef enum ADS1115_MEASURE_MODE{
    ADS1115_CONTINUOUS = 0x0000, 
    ADS1115_SINGLE     = 0x0100,
    ADS1015_CONTINUOUS = ADS1115_CONTINUOUS,
    ADS1015_SINGLE     = ADS1115_SINGLE 
} measureMode;

typedef enum ADS1115_RANGE{
    ADS1115_RANGE_6144  = 0x0000,
    ADS1115_RANGE_4096  = 0x0200,
    ADS1115_RANGE_2048  = 0x0400,
    ADS1115_RANGE_1024  = 0x0600,
    ADS1115_RANGE_0512  = 0x0800,
    ADS1115_RANGE_0256  = 0x0A00,
    ADS1015_RANGE_6144  = ADS1115_RANGE_6144,
    ADS1015_RANGE_4096  = ADS1115_RANGE_4096,
    ADS1015_RANGE_2048  = ADS1115_RANGE_2048,
    ADS1015_RANGE_1024  = ADS1115_RANGE_1024,
    ADS1015_RANGE_0512  = ADS1115_RANGE_0512,
    ADS1015_RANGE_0256  = ADS1115_RANGE_0256
} range;

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
        bool init(bool ads1015 = false){return true;};
        void setVoltageRange_mV(ADS1115_RANGE range) {};
        void setMeasureMode(ADS1115_MEASURE_MODE mode){};
        void setCompareChannels(ADS1115_MUX mux){};
        float getResult_mV(){ return 3500.0f;}
};


#endif //ADS1115_WE_H