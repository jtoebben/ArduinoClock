#ifndef CLOCK_H
#define CLOCK_H

//RTC Modul
#include "DS3231.h"

//LED Strip
#include <Adafruit_NeoPixel.h>
#define LEDS 58 //Gesamtanzahl an LEDs
#define PinStrip 10 //Datenpin für die LEDs

class Clock { 
  protected:   
    DS3231 *c = new DS3231;   //RTC Modul Klasse    
    Adafruit_NeoPixel *pixel = new Adafruit_NeoPixel(LEDS, PinStrip, NEO_RGB + NEO_KHZ400); //LED Streifen
    bool dots = true; //Status der Punkte
    
  public:
    Clock();
    ~Clock();
    void setHour(byte);
    void setMinute(byte);
    void setSecond(byte);
    byte getHour();    
    byte getMinute();    
    byte getSecond();
    virtual void saveNumberInSevenSegment(byte,byte);
    virtual void updateDots();
    void showTime();    
};

#endif
