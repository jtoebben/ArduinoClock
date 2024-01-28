#ifndef CLOCK_CPP
#define CLOCK_CPP
#include "Clock.h"

//Konstruktor
Clock::Clock() {
  Wire.begin();
  pixel->begin();  
  pixel->setBrightness(255);
}

//Dekonstruktor
Clock::~Clock() {
  delete c;
  delete pixel;
}

//Setzen der Stunde
void Clock::setHour(byte hour) {
  if(hour >= 0 && hour <= 24) this->c->setHour(hour); 
}

//Setzen der Minute
void Clock::setMinute(byte minute) {
  if(minute >= 0 && minute <= 60) this->c->setMinute(minute);
}

//Setzen der Sekunden
void Clock::setSecond(byte second) {
  if(second >= 0 && second <= 60) this->c->setSecond(second);  
}

//Rückgabe der Stunden
byte Clock::getHour() {
  bool h12;
  bool pm;
  return this->c->getHour(h12, pm);
}

//Rückgabe der Minute
byte Clock::getMinute() {
  return this->c->getMinute();
}

//Rückgabe der Sekunde
byte Clock::getSecond() {
  return this->c->getSecond();
}

//Anzeigen der Zahl auf einen Display
void Clock::saveNumberInSevenSegment(byte disp, byte number) {
      byte numberSevenSegment[10][14] = {
      {1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14},        //0
      {2, 1, 9, 10},                                    //1
      {4, 3, 2, 1, 8, 7, 14, 13, 12, 11},               //2
      {4, 3, 2, 1, 8, 7, 9, 10, 11, 12},                //3
      {5, 6, 7, 8, 1, 2, 9, 10},                        //4
      {3, 4, 5, 6, 7, 8, 9, 10, 11, 12},                //5
      {5, 6, 14, 13, 12, 11, 10, 9, 8, 7, 4, 3},        //6
      {4, 3, 2, 1, 9, 10},                              //7
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},  //8
      {6, 5, 4, 3, 2, 1, 8, 7, 9, 10, 11, 12}           //9
    };

  //Setze LED Farben
  for(byte i = 0; i <= sizeof(numberSevenSegment[number]); i++)
  {
    byte led = numberSevenSegment[number][i];
    if(led > 0) //Leeres Array Sellen nicht bearbeiten
    {
      led = led + 14 * disp; //4 Anzeigen mit 14 Pixel
      if (disp >= 2) led = led + 2; //Zwei Punkte nach zwei Anzeigen

      //Pixel Farbe setzen
      pixel->setPixelColor((led - 1), pixel->Color(255, 255, 255));      
    }
    else
    {
      break;
    }
  }
}

//Punkte aktualisieren
void Clock::updateDots() {
    if(dots) {
        pixel->setPixelColor(28, pixel->Color(255, 255, 255));
        pixel->setPixelColor(29, pixel->Color(255, 255, 255));
    }
    else
    {
      pixel->setPixelColor(28, pixel->Color(0, 0, 0));
      pixel->setPixelColor(29, pixel->Color(0, 0, 0));  
    }    
    dots = !dots;
}

//Anzeigen der Uhrzeit
void Clock::showTime() {  
    byte hour = this->getHour();
    byte minute = this->getMinute();
    
    pixel->clear();
    saveNumberInSevenSegment(0, (byte)(minute % 10));
    saveNumberInSevenSegment(1, (byte)(minute / 10));
    saveNumberInSevenSegment(2, (byte)(hour % 10));
    saveNumberInSevenSegment(3, (byte)(hour / 10));
    updateDots();
    pixel->show();
}


    
#endif
