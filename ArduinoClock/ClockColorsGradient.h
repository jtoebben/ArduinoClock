#ifndef CLOCKCOLORSGRADIENT_H
#define CLOCKCOLORSGRADIENT_H
#include "Clock.h"

class ClockColorsGradient:public Clock {
  public:
    ClockColorsGradient();
    ~ClockColorsGradient();
    void saveNumberInSevenSegment(byte, byte);
    void setColor(byte, byte, byte);
    void dezFarbe(byte, int);
    void updateDots();
};

#endif
