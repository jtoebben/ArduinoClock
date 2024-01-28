#include "ClockColorsGradient.h"

//Erstelllung eines Uhr Objektes
ClockColorsGradient* Cl = new ClockColorsGradient;

void setup() {

}

void loop() {
  Cl->showTime();
  delay(1000);
}
