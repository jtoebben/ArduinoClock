#ifndef CLOCKCOLOR_CPP
#define CLOCKCOLOR_CPP

#include "ClockColor.h"

//Konstruktor
ClockColor::ClockColor(byte red, byte green, byte blue):red(red), green(green), blue(blue) {
  Wire.begin();
  pixel->begin();  
  pixel->setBrightness(255);
}

//Dekonstruktor
ClockColor::~ClockColor() {
  delete c;
  delete pixel;
}

//Anzeigen der Zahl auf einen Display
void ClockColor::saveNumberInSevenSegment(byte disp, byte number) {
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
      pixel->setPixelColor((led - 1), pixel->Color(green, red, blue));      
    }
    else
    {
      break;
    }
  }
}

//Setzen der Farbe
void ClockColor::setColor(byte red, byte green, byte blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

//Punkte aktualisieren
void ClockColor::updateDots() {
    if(dots) {
        pixel->setPixelColor(28, pixel->Color(green, red, blue));
        pixel->setPixelColor(29, pixel->Color(green, red, blue));
    }
    else
    {
      pixel->setPixelColor(28, pixel->Color(0, 0, 0));
      pixel->setPixelColor(29, pixel->Color(0, 0, 0));  
    }    
    dots = !dots;
}

//Rückgabe des Farbwertes Rot
byte ClockColor::getRed() {
  return this->red;
}

//Rückgabe des Farbwertes Grün
byte ClockColor::getGreen() {
  return this->green;
}

//Rückgabe des Farbwertes Blau
byte ClockColor::getBlue() {
  return this->blue;
}

#endif
