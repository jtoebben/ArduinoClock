#ifndef CLOCKRED_H
#define CLOCKRED_H
#include "Clock.h"

class ClockColor:public Clock {
  private:
    byte red = 0;
    byte green = 0;
    byte blue = 0;
      
  public:
    ClockColor(byte,byte,byte);
    ~ClockColor();
    void saveNumberInSevenSegment(byte, byte);
    void setColor(byte, byte, byte);
    void updateDots();
    byte getRed();
    byte getGreen();
    byte getBlue();
};

#endif
