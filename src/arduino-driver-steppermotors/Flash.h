/*
 * Guillaume RIVIERE (2026)
 */

#ifndef FLASH_HPP
#define FLASH_HPP

//To disable pragma messages on compile
//include this Before including FastLED.h
#define FASTLED_INTERNAL

//-- Libraries

#include <FastLED.h>//https://github.com/FastLED/FastLED

//-- FastLED constants

#define NUM_STRIPS 1
#define NUM_LEDS 65
#define BRIGHTNESS 80
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define FASTLED_ALLOW_INTERRUPTS 0
//#define FASTLED_INTERRUPT_RETRY_COUNT 1
#define FRAMES_PER_SECOND 60
#define COOLING 55
#define SPARKING 120

//-- Parameters

#define SATURATION 255
#define MAX_GAIN 10
#define MIN_GAIN -10
#define DELTA_FROM_GAIN_TO_LEVEL_INDEX 10
#define NUM_LEVELS 21

//-- Types

typedef CRGB CRGB_strip[NUM_LEDS];

//-- Classes

class CFlash {

public:
  
  CFlash();

  inline CRGB_strip &leds() { return m_leds; }
  
  void init(uint8_t saturation, uint8_t luminosity);
  
  void splash();
  
  void setSaturation(uint8_t value);

  void setLuminosity(uint8_t value);

  void setGain(int8_t value, bool fade); /* gain ranges in [MIN_GAIN ; MAX_GAIN] */

  void turnLightOff();
  
protected:
  
  void reset();

  void update();

  void fadeOut();

  void fadeIn();

  void setLevel(int8_t level, uint8_t h, uint8_t s, uint8_t v);

private:
  
  int8_t m_gain ;

  uint8_t m_saturation;

  uint8_t m_luminosity;

  bool m_light_on;

  CRGB_strip m_leds;

};

#endif /* FLASH_HPP */
