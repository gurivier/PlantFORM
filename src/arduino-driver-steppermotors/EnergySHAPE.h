/*
 * Guillaume RIVIERE (2026)
 */

#ifndef ENERGYSHAPE_HPP
#define ENERGYSHAPE_HPP

#include "Flash.h"

//-- Parameters

#define NUM_DAYS 1 // in [1 .. 5]

//-- Arduino pins

#define STRIP_PIN_DAY0 4
#define STRIP_PIN_DAY1 5
#define STRIP_PIN_DAY2 6
#define STRIP_PIN_DAY3 7
#define STRIP_PIN_DAY4 8

//-- Class

class CEnergySHAPE {

public:
  
  void init();

  void setGainForDay(unsigned char day, char value, bool fade); // day in [0 .. NUM_DAYS-1], value in [MIN_GAIN .. MAX_GAIN]

  void setGainForAll(char value, bool fade); // value in [MIN_GAIN .. MAX_GAIN]

  void setSaturationForDay(unsigned char day, char value);

  void setSaturationForAll(char value);

  void setLuminosityForDay(unsigned char day, char value);

  void setLuminosityForAll(char value);

  void turnLightOffForDay(unsigned char day);

  void turnLightOffForAll();

private:

  CFlash flashes[NUM_DAYS];

};

//-- Objects

extern CEnergySHAPE EnergySHAPE;

#endif /* ENERGYSHAPE_HPP */
