#include <FastLED.h>//https://github.com/FastLED/FastLED

#include <pt.h>

#include "led_strip.hpp"
#include "event_utils.h"

#include "hsv_colors.h"

//-- MACRO CONSTANTS

#define NUM_STRIPS 1
#define NUM_LEDS 10
#define BRIGHTNESS 100
#define LED_TYPE WS2812B
//#define COLOR_ORDER BRG
//#define COLOR_ORDER BGR
//#define COLOR_ORDER BRG
#define COLOR_ORDER GRB // For use with HSV
#define FASTLED_ALLOW_INTERRUPTS 0
#ifdef FASTLED_INTERRUPT_RETRY_COUNT
#undef FASTLED_INTERRUPT_RETRY_COUNT
#endif
#define FASTLED_INTERRUPT_RETRY_COUNT 1
#define FRAMES_PER_SECOND 60
#define COOLING 55
#define SPARKING 120

#define STRIP_PIN 3

//-- GLOBALS

uint16_t blink_period_ms = 400 ;

static struct pt pt ;

HSV colors[NUM_LEDS] ;
HSV blinking_colors[NUM_LEDS] ;
bool is_blinking[NUM_LEDS] ;

CRGB leds[NUM_LEDS] ;

LEDEvent firstLEDEvent = NULL ;
LEDEvent lastLEDEvent = NULL ;

//-- FUNCTIONS

void init_leds () {
  
  //Init led strips
  FastLED.addLeds<LED_TYPE, STRIP_PIN, COLOR_ORDER>(leds, NUM_LEDS) ;
  FastLED.setBrightness(BRIGHTNESS) ;

  for (uint8_t i = 0 ; i < NUM_LEDS ; i++) {
    colors[i] = { 0, 0, 0 } ;
    leds[i].setRGB(0, 0, 0) ; // R B G
  }

  PT_INIT(&pt) ;

  delay(1000) ;
}

void set_led_rgb (uint8_t hour, uint8_t r, uint8_t g, uint8_t b) {
  if (hour == 0) {
    for (uint8_t i = 0 ; i < NUM_LEDS ; i++) {
      leds[i].setRGB(r, g, b) ;
    }
  }
  else {
    leds[hour-1].setRGB(r, g, b) ;
  }
  FastLED.show() ;
}

void set_led (uint8_t hour, uint8_t h, uint8_t s, uint8_t v) {
  if (hour == 0) {
    for (uint8_t i = 0 ; i < NUM_LEDS ; i++) {
      colors[i] = { h, s, v } ;
      leds[i] = CHSV(h, s, v) ;
    }
  }
  else {
    colors[hour-1] = { h, s, v } ;
    leds[hour-1] = CHSV(h, s, v) ;
  }
  FastLED.show() ;
}

void set_blink_period_ms (uint16_t period_ms) {
  blink_period_ms = period_ms ;
}

void add_led_start_blink_event (int16_t *values) {
  LEDEvent evt ;

  if ((evt = (LEDEvent)malloc (sizeof(struct led_event))) == NULL) {
    Serial.print(F("Allocation error\n")) ;
  }
  else {
    evt->type = LED_EVENT_TYPE_START_BLINK ;
    evt->value.color.hour = *values ;
    evt->value.color.h = *(values+1) ;
    evt->value.color.s = *(values+2) ;
    evt->value.color.v = *(values+3) ;
    PUSH_EVENT(firstLEDEvent, lastLEDEvent, evt) ;
  }
}

void add_led_stop_blink_event (int16_t *values) {
  LEDEvent evt ;

  if ((evt = (LEDEvent)malloc (sizeof(struct led_event))) == NULL) {
    Serial.print(F("Allocation error\n")) ;
  }
  else {
    evt->type = LED_EVENT_TYPE_STOP_BLINK ;
    evt->value.num = *values ;
    PUSH_EVENT(firstLEDEvent, lastLEDEvent, evt) ;
  }
}

void add_led_color_event (uint8_t hour, uint8_t h, uint8_t s, uint8_t v) {
  LEDEvent evt ;

  if ((evt = (LEDEvent)malloc (sizeof(struct led_event))) == NULL) {
    Serial.print(F("Allocation error\n")) ;
  }
  else {
    evt->type = LED_EVENT_TYPE_COLOR ;
    evt->value.color.hour = hour ;
    evt->value.color.h = h ;
    evt->value.color.s = s ;
    evt->value.color.v = v ;
    PUSH_EVENT(firstLEDEvent, lastLEDEvent, evt) ;
  }
}

void add_led_color_event (int16_t *values) {
  LEDEvent evt ;

  if ((evt = (LEDEvent)malloc (sizeof(struct led_event))) == NULL) {
    Serial.print(F("Allocation error\n")) ;
  }
  else {
    evt->type = LED_EVENT_TYPE_COLOR ;
    evt->value.color.hour = *values ;
    evt->value.color.h = *(values+1) ;
    evt->value.color.s = *(values+2) ;
    evt->value.color.v = *(values+3) ;
    PUSH_EVENT(firstLEDEvent, lastLEDEvent, evt) ;
  }
}

void add_led_wait_event (uint16_t delay_ms) {
  LEDEvent evt ;

  if ((evt = (LEDEvent)malloc (sizeof(struct led_event))) == NULL) {
    Serial.print(F("Allocation error\n")) ;
  }
  else {
    evt->type = LED_EVENT_TYPE_WAIT ;
    evt->value.delay_ms = delay_ms ;
    PUSH_EVENT(firstLEDEvent, lastLEDEvent, evt) ;
  }
}

static int protothreadBlink(struct pt *pt)
{
  static unsigned long lastTimeBlink = 0 ;
  PT_BEGIN(pt) ;
  while(1) {
    lastTimeBlink = millis() ;
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > blink_period_ms) ;
    for (uint8_t i = 0 ; i < NUM_LEDS ; i++) {
      if (is_blinking[i]) {
        leds[i] = CHSV(blinking_colors[i].h, blinking_colors[i].s, blinking_colors[i].v) ;
      }
    }
    FastLED.show() ;    

    lastTimeBlink = millis() ;
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > blink_period_ms) ;
    for (uint8_t i = 0 ; i < NUM_LEDS ; i++) {
      if (is_blinking[i]) {
        leds[i] = CHSV(colors[i].h, colors[i].s, colors[i].v) ;
      }
    }
    FastLED.show() ;    
  }
  PT_END(pt) ;
}

void run_leds () {
  if (firstLEDEvent != NULL) {
    switch (firstLEDEvent->type) {
    case LED_EVENT_TYPE_COLOR:
    {
      set_led(firstLEDEvent->value.color.hour, firstLEDEvent->value.color.h, firstLEDEvent->value.color.s, firstLEDEvent->value.color.v) ;
    }
    break ;
    case LED_EVENT_TYPE_WAIT:
    {
      delay(firstLEDEvent->value.delay_ms) ;
    }
    break ;   
    case LED_EVENT_TYPE_STOP_BLINK:
    {
      uint8_t j = firstLEDEvent->value.num - 1;
      is_blinking[j] = false ;
      set_led(j+1, colors[j].h, colors[j].s, colors[j].v) ;
    }
    break ;
    case LED_EVENT_TYPE_START_BLINK:
    {
      uint8_t i = firstLEDEvent->value.color.hour - 1 ;
      blinking_colors[i].h = firstLEDEvent->value.color.h ;
      blinking_colors[i].s = firstLEDEvent->value.color.s ;
      blinking_colors[i].v = firstLEDEvent->value.color.v ;
      is_blinking[i] = true ;
    }
    break ;
    default:
      Serial.print(F("Unknown LED event.")) ;
    }
    POP_EVENT(LEDEvent, firstLEDEvent) ;
  }
  protothreadBlink(&pt);
}
