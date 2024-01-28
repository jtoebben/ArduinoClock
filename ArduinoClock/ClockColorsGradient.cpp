#ifndef CLOCKCOLORSGRADIENT_CPP
#define CLOCKCOLORSGRADIENT_CPP
#include "ClockColorsGradient.h"

//Konstruktor
ClockColorsGradient::ClockColorsGradient() {
  Wire.begin();
  pixel->begin();  
  pixel->setBrightness(255);
}

//Dekonstruktor
ClockColorsGradient::~ClockColorsGradient() {
  delete c;
  delete pixel;
}

//Dezimalwert in Farbewerte
void ClockColorsGradient::dezFarbe(byte led, int farbe) {
  int red = 0;
  int green = 0;
  int blue = 0;
  int modi = 0;
  if (farbe > 1530) farbe = farbe - (1530 * (farbe / 1530));

  if (farbe >= 0)
  {
    if (farbe <= 255)
    {
      red = 255;
      green = farbe;
      blue = 0;
      modi = 1;
    }
    else if (farbe <= 510)
    {
      red = 255 - (farbe - 255);
      green = 255;
      blue = 0;
      modi = 2;
    }
    else if (farbe <= 765)
    {
      red = 0;
      green = 255;
      blue =  farbe - 510;
      modi = 3;
    }
    else if (farbe <= 1020)
    {
      red = 0;
      green = 255 - (farbe - 765);
      blue = 255;
      modi = 4;
    }
    else if  (farbe <= 1275)
    {
      red = farbe - 1020;
      green = 0;
      blue = 255;
      modi = 5;
    }
    else if (farbe <= 1536)
    {
      red = 255;
      green = 0;
      blue = 255 - (farbe - 1275);
      modi = 6;
    }
  }
  pixel->setPixelColor(led, pixel->Color(red, green, blue));
}

//Anzeigen der Zahl auf einen Display
void ClockColorsGradient::saveNumberInSevenSegment(byte disp, byte number) {
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
      dezFarbe((led - 1), (1530 / pixel->numPixels() * (led - 1)));     
    }
    else
    {
      break;
    }
  }
}

//Punkte aktualisieren
void ClockColorsGradient::updateDots() {
    if(dots) {
        dezFarbe(28, (1530 / pixel->numPixels() * 28)); 
        dezFarbe(29, (1530 / pixel->numPixels() * 29)); 
    }
    else
    {
      pixel->setPixelColor(28, pixel->Color(0, 0, 0));
      pixel->setPixelColor(29, pixel->Color(0, 0, 0));  
    }    
    dots = !dots;
}

#endif
