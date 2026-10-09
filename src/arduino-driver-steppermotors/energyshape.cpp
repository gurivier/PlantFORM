
#include "energyshape.hpp"

//To disable pragma messages on compile
//include this Before including FastLED.h
#define FASTLED_INTERNAL

//Libraries
#include <FastLED.h>//https://github.com/FastLED/FastLED

//Constants
#define NUM_STRIPS 1
#define NUM_LEDS 65
#define BRIGHTNESS 100
#define LED_TYPE WS2812B
#define COLOR_ORDER RGB // BRG
#define FASTLED_ALLOW_INTERRUPTS 0
//#define FASTLED_INTERRUPT_RETRY_COUNT 1
#define FRAMES_PER_SECOND 60
#define COOLING 55
#define SPARKING 120

//HSV "Rainbow" colors
//https://github.com/FastLED/FastLED/wiki/FastLED-HSV-Colors
#define H_RED    0
#define H_HONEY 38
#define H_GREEN 96

//Parameters
#define STRIP_PIN 4
#define NUM_LEVELS 21

//Variables
int levels[NUM_LEVELS][7] = {
  { 11, -1, -1, -1, -1, -1, -1 },
  { 12, -1, -1, -1, -1, -1, -1 },
  { 13, 48, -1, -1, -1, -1, -1 },
  { 14, 47, -1, -1, -1, -1, -1 },
  { 15, 46, 49, -1, -1, -1, -1 },
  { 16, 45, 50, -1, -1, -1, -1 },
  { 17, 44, 51, 62, -1, -1, -1 },
  { 18, 43, 52, 61, -1, -1, -1 },
  { 19, 42, 53, 60, -1, -1, -1 },
  {  0, 10, 20, 41, 54, 59, 63 },
  {  1,  9, 21, 40, 55, 58, 64 },
  {  2,  8, 22, 39, 56, 57, -1 },
  {  3,  7, 23, 38, -1, -1, -1 },
  {  6, 24, 37, -1, -1, -1, -1 },
  {  5, 25, 36, -1, -1, -1, -1 },
  {  4, 26, 35, -1, -1, -1, -1 },
  { 27, 34, -1, -1, -1, -1, -1 },
  { 28, 33, -1, -1, -1, -1, -1 },
  { 29, 32, -1, -1, -1, -1, -1 },
  { 31, -1, -1, -1, -1, -1, -1 },
  { 30, -1, -1, -1, -1, -1, -1 }
};

int levels_len[NUM_LEVELS] = { 1, 1, 2, 2, 3, 3, 4, 4, 4, 7, 7, 6, 4, 3, 3, 3, 2, 2, 2, 1, 1 };

unsigned char es_brightness = BRIGHTNESS;

//Objects
CRGB es_leds[NUM_LEDS];

void ledReset() {  
  for (int i = 0; i < NUM_LEDS ; i++) {
    es_leds[i].setRGB(0, 0, 0); // G R B
  }
  FastLED.show();
}

void setLevel(int level, unsigned char h, unsigned char s, unsigned char v) {
  int j = level + 10;
  for (int k = 0; k < levels_len[j] ; k++) {
    int i = levels[j][k];
    es_leds[i] = CHSV(h, s, v);
  }
}

void energyshape_init() {
  //Init Serial USB
  //Serial.begin(9600);
  //Serial.println(F("Initialize System"));
  //Init led strips
  FastLED.addLeds<LED_TYPE, STRIP_PIN, COLOR_ORDER>(es_leds, NUM_LEDS);
  //FastLED.setBrightness( es_brightness ); // 0 .. 255

  ledReset();
}

void energyshape_set_brightness(unsigned char value) { // [0, 255]
  es_brightness = value;
}

void energyshape_set_gain(char value) { // [-10, +10] + 32 + 64
  int l;
  
  for (int i = 0; i < NUM_LEDS ; i++) {
    es_leds[i].setRGB(0, 0, 0); // G R B
  }

  if (value != 64) {

    l = 0;
    setLevel(l, H_HONEY, 255, es_brightness); // H S L
      
    if (value < 0) {
      if (value < -10) {
        value = -10;
      }
      for (l = -1 ; l >= value ; l--) {
        setLevel(l, H_GREEN, 255, es_brightness); // H S L
      }
    }
    else if (value > 0) {
      if (value > 10) {
        value = 10;
      }
      for (l = 1 ; l <= value ; l++) {
        setLevel(l, H_RED, 255, es_brightness); // H S L
      }
    }
  }
  
  FastLED.show();;
}
