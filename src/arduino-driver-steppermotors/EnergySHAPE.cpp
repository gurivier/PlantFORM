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

void CEnergySHAPE::setGainForDay(unsigned char day, char value, bool fade)
{
  flashes[day].setGain (value, fade);
}

void CEnergySHAPE::setGainForAll(char value, bool fade)
{
  for (int day = 0 ; day < NUM_DAYS ; day++) {
    flashes[day].setGain (value, fade);
  }
}

void CEnergySHAPE::setSaturationForDay(unsigned char day, char value)
{
  flashes[day].setSaturation (value);
}

void CEnergySHAPE::setSaturationForAll(char value)
{
  for (int day = 0 ; day < NUM_DAYS ; day++) {
    flashes[day].setSaturation (value);
  }
}

void CEnergySHAPE::setLuminosityForDay(unsigned char day, char value)
{
  flashes[day].setLuminosity (value);
}

void CEnergySHAPE::setLuminosityForAll(char value)
{
  for (int day = 0 ; day < NUM_DAYS ; day++) {
    flashes[day].setLuminosity (value);
  }
}

void CEnergySHAPE::turnLightOffForDay(unsigned char day)
{
  flashes[day].turnLightOff();
}

void CEnergySHAPE::turnLightOffForAll()
{
  for (int day = 0 ; day < NUM_DAYS ; day++) {
    flashes[day].turnLightOff();
  }
}
