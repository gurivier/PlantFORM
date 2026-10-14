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

  void splash();

  void setGainForDay(uint8_t day, int8_t value, bool fade); // day in [0 .. NUM_DAYS-1], value in [MIN_GAIN .. MAX_GAIN]

  void setGainForAll(int8_t value, bool fade); // value in [MIN_GAIN .. MAX_GAIN]

  void setSaturationForDay(uint8_t day, int8_t value);

  void setSaturationForAll(int8_t value);

  void setLuminosityForDay(uint8_t day, int8_t value);

  void setLuminosityForAll(int8_t value);

  void turnLightOffForDay(uint8_t day);

  void turnLightOffForAll();

private:

  CFlash flashes[NUM_DAYS];

};

//-- Objects

extern CEnergySHAPE EnergySHAPE;

#endif /* ENERGYSHAPE_HPP */
