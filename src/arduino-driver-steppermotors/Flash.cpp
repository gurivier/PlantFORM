/*
 * Guillaume RIVIERE (2026)
 */

#include "Flash.h"

//-- Color hues (FastLED "Rainbow")

#define H_BRICK  0
#define H_HONEY 64
#define H_GRASS 96

//-- Variables

unsigned char g_levels[NUM_LEDS] = {
  11, // -10 (MIN GAIN)
  12, // -9
  13, 48, // -8
  14, 47, // -7
  15, 46, 49, // -6
  16, 45, 50, // -5
  17, 44, 51, 62, // -4
  18, 43, 52, 61, // -3
  19, 42, 53, 60, // -2
  0, 10, 20, 41, 54, 59, 63, // -1
  1,  9, 21, 40, 55, 58, 64, // 0 (ZERO GAIN)
  2,  8, 22, 39, 56, 57, // 1
  3,  7, 23, 38, // 2
  6, 24, 37, // 3
  5, 25, 36, // 4
  4, 26, 35, // 5
  27, 34, // 6
  28, 33, // 7
  29, 32, // 8
  31, // 9
  30 // 10 (MAX GAIN)
};

unsigned char g_levels_indexes[NUM_LEVELS + 1] = {
  0, 1, 2, 4, 6, 9, 12, 16, 20, 24, 31, 38, 44, 48, 51, 54, 57, 59, 61, 63, 64, 65
};


//-- Constructor

CFlash::CFlash()
: m_gain(0),
  m_saturation(128),
  m_luminosity(BRIGHTNESS),
  m_light_on(false)
{
  // Nothing
}

//-- Methods

void CFlash::init(unsigned char saturation, unsigned char luminosity)
{  
  m_saturation = saturation;
  m_luminosity = luminosity;

  for (int i = 0; i < NUM_LEDS ; i++) {
    m_leds[i].setRGB(0, 0, 0);
  }

  FastLED.show();
}

void CFlash::setSaturation(unsigned char value)
{  
  m_saturation = value;
  
  if (m_light_on) {
    this->update();
  }
}

void CFlash::setLuminosity(unsigned char value)
{  
  m_luminosity = value;
  
  if (m_light_on) {
    this->update();
  }
}

void CFlash::turnLightOff()
{  
  m_light_on = false;
  
  for (int i = 0; i < NUM_LEDS ; i++) {
    m_leds[i].setRGB(0, 0, 0);
  }

  FastLED.show();
}

void CFlash::setGain(char value, bool fade)
{
  if (fade) {
    this->fadeOut();
  }
  this->reset();

  if (m_gain < MIN_GAIN) {
    m_gain = MIN_GAIN;
  }
  else if (value > MAX_GAIN) {
    value = MAX_GAIN;
  }
  else {
    m_gain = value;
  }
  
  if (fade) {
    this->fadeIn();
  }
  this->update();
}

void CFlash::reset()
{
  for (int i = 0; i < NUM_LEDS ; i++) {
    m_leds[i].setRGB(0, 0, 0);
  }

  this->setLevel(0, H_HONEY, m_saturation, m_luminosity);
}

void CFlash::update()
{   
  if (m_gain < 0) {
    for (int level = -1 ; level >= m_gain ; level--) {
      this->setLevel(level, H_GRASS, m_saturation, m_luminosity);
    }
  }
  else if (m_gain > 0) {
    for (int level = 1 ; level <= m_gain ; level++) {
      this->setLevel(level, H_BRICK, m_saturation, m_luminosity);
    }
  }

  m_light_on = true;
    
  FastLED.show();
}

void CFlash::fadeOut()
{
  if (m_light_on) {
    if (m_gain < 0) {
      int step = m_luminosity * 0.1;
      for (int luminosity = m_luminosity ; luminosity > 0 ; luminosity -= step) {
        for (int level = -1 ; level >= m_gain ; level--) {
          this->setLevel(level, H_GRASS, m_saturation, luminosity);
        }
        FastLED.show();
        delay(200);
      }
    }
    else if (m_gain > 0) {
      int step = m_luminosity * 0.1;
      for (int luminosity = m_luminosity ; luminosity > 0 ; luminosity -= step) {
        for (int level = 1 ; level <= m_gain ; level++) {
          this->setLevel(level, H_BRICK, m_saturation, luminosity);
        }
        FastLED.show();
        delay(200);
      }
    }
  }
}

void CFlash::fadeIn()
{
  if (m_gain < 0) {
    int step = m_luminosity * 0.1;
    for (float luminosity = 0 ; luminosity < m_luminosity ; luminosity += step) {
      for (int level = -1 ; level >= m_gain ; level--) {
        this->setLevel(level, H_GRASS, m_saturation, luminosity);
      }
      FastLED.show();
      delay(200);
    }
  }
  else if (m_gain > 0) {
    int step = m_luminosity * 0.1;
    for (int luminosity = 0 ; luminosity < m_luminosity ; luminosity += step) {
      for (int level = 1 ; level <= m_gain ; level++) {
        this->setLevel(level, H_BRICK, m_saturation, luminosity);
      }
      FastLED.show();
      delay(200);
    }
  }
}

void CFlash::setLevel(char level, unsigned char h, unsigned char s, unsigned char v)
{
  int j = level + DELTA_FROM_GAIN_TO_LEVEL_INDEX;
  
  for (int k = g_levels_indexes[j] ; k < g_levels_indexes[j+1] ; k++) {
    int i = g_levels[k];
    m_leds[i] = CHSV(h, s, v);
  }
}
