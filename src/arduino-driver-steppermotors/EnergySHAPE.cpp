/*
 * Guillaume RIVIERE (2026)
 */

//-- Libraries

#include <FastLED.h>//https://github.com/FastLED/FastLED

#include "EnergySHAPE.h"

//-- Objects

CEnergySHAPE EnergySHAPE;

//-- Methods

void CEnergySHAPE::init()
{
  FastLED.addLeds<LED_TYPE, STRIP_PIN_DAY0, COLOR_ORDER>(flashes[0].leds(), NUM_LEDS);
  flashes[0].init(SATURATION, BRIGHTNESS);

#if NUM_DAYS >= 2
  FastLED.addLeds<LED_TYPE, STRIP_PIN_DAY1, COLOR_ORDER>(flashes[1].leds(), NUM_LEDS);
  flashes[1].init(SATURATION, BRIGHTNESS);
#endif

#if NUM_DAYS >= 3
  FastLED.addLeds<LED_TYPE, STRIP_PIN_DAY2, COLOR_ORDER>(flashes[2].leds(), NUM_LEDS);
  flashes[2].init(SATURATION, BRIGHTNESS);
#endif

#if NUM_DAYS >= 4
  FastLED.addLeds<LED_TYPE, STRIP_PIN_DAY3, COLOR_ORDER>(flashes[3].leds(), NUM_LEDS);
  flashes[3].init(SATURATION, BRIGHTNESS);
#endif

#if NUM_DAYS >= 5
  FastLED.addLeds<LED_TYPE, STRIP_PIN_DAY4, COLOR_ORDER>(flashes[4].leds(), NUM_LEDS);
  flashes[4].init(SATURATION, BRIGHTNESS);
#endif
}

void CEnergySHAPE::splash()
{
  for (uint8_t day = 0 ; day < NUM_DAYS ; day++) {
    flashes[day].splash ();
  }  
}

void CEnergySHAPE::setGainForDay(uint8_t day, int8_t value, bool fade)
{
  flashes[day].setGain (value, fade);
}

void CEnergySHAPE::setGainForAll(int8_t value, bool fade)
{
  for (uint8_t day = 0 ; day < NUM_DAYS ; day++) {
    flashes[day].setGain (value, fade);
  }
}

void CEnergySHAPE::setSaturationForDay(uint8_t day, int8_t value)
{
  flashes[day].setSaturation (value);
}

void CEnergySHAPE::setSaturationForAll(int8_t value)
{
  for (uint8_t day = 0 ; day < NUM_DAYS ; day++) {
    flashes[day].setSaturation (value);
  }
}

void CEnergySHAPE::setLuminosityForDay(uint8_t day, int8_t value)
{
  flashes[day].setLuminosity (value);
}

void CEnergySHAPE::setLuminosityForAll(int8_t value)
{
  for (uint8_t day = 0 ; day < NUM_DAYS ; day++) {
    flashes[day].setLuminosity (value);
  }
}

void CEnergySHAPE::turnLightOffForDay(uint8_t day)
{
  flashes[day].turnLightOff();
}

void CEnergySHAPE::turnLightOffForAll()
{
  for (uint8_t day = 0 ; day < NUM_DAYS ; day++) {
    flashes[day].turnLightOff();
  }
}
