

#include "Trunk.h"
#include "event_utils.h"

#include "hsv_colors.h"

//-- Macro Constants

#define NUM_STRIPS 1
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

//-- Objects

CTrunk Trunk;

//-- Globals

static struct pt pt ;

//-- Methods

void CTrunk::init_leds () {
  
  //Init led strips
  FastLED.addLeds<LED_TYPE, STRIP_PIN, COLOR_ORDER>(leds, NUM_LEDS) ;
  FastLED.setBrightness(BRIGHTNESS) ;

  for (uint8_t i = 0 ; i < NUM_LEDS ; i++) {
    this->colors[i] = { 0, 0, 0 } ;
    this->leds[i].setRGB(0, 0, 0) ; // R B G
  }

  PT_INIT(&pt) ;

  delay(1000) ;
}

void CTrunk::set_led_rgb (uint8_t hour, uint8_t r, uint8_t g, uint8_t b) {
  if (hour == 0) {
    for (uint8_t i = 0 ; i < NUM_LEDS ; i++) {
      this->leds[i].setRGB(r, g, b) ;
    }
  }
  else {
    this->leds[hour-1].setRGB(r, g, b) ;
  }
  FastLED.show() ;
}

void CTrunk::set_led_hsv (uint8_t hour, uint8_t h, uint8_t s, uint8_t v) {
  if (hour == 0) {
    for (uint8_t i = 0 ; i < NUM_LEDS ; i++) {
      this->colors[i] = { h, s, v } ;
      this->leds[i] = CHSV(h, s, v) ;
    }
  }
  else {
    this->colors[hour-1] = { h, s, v } ;
    this->leds[hour-1] = CHSV(h, s, v) ;
  }
  FastLED.show() ;
}

void CTrunk::set_blink_period_ms (uint16_t period_ms) {
  this->blink_period_ms = period_ms ;
}

void CTrunk::add_led_start_blink_event (int16_t *values) {
  LEDEvent evt ;

  if ((evt = (LEDEvent)malloc (sizeof(struct led_event))) == NULL) {
    Serial.print(F("Allocation error\n")) ;
    Serial.flush();
  }
  else {
    evt->type = LED_EVENT_TYPE_START_BLINK ;
    evt->value.color.hour = *values ;
    evt->value.color.h = *(values+1) ;
    evt->value.color.s = *(values+2) ;
    evt->value.color.v = *(values+3) ;
    PUSH_EVENT(this->firstLEDEvent, this->lastLEDEvent, evt) ;
  }
}

void CTrunk::add_led_stop_blink_event (int16_t *values) {
  LEDEvent evt ;

  if ((evt = (LEDEvent)malloc (sizeof(struct led_event))) == NULL) {
    Serial.print(F("Allocation error\n")) ;
    Serial.flush();
  }
  else {
    evt->type = LED_EVENT_TYPE_STOP_BLINK ;
    evt->value.num = *values ;
    PUSH_EVENT(this->firstLEDEvent, this->lastLEDEvent, evt) ;
  }
}

void CTrunk::add_led_color_event (uint8_t hour, uint8_t h, uint8_t s, uint8_t v) {
  LEDEvent evt ;

  if ((evt = (LEDEvent)malloc (sizeof(struct led_event))) == NULL) {
    Serial.print(F("Allocation error\n")) ;
    Serial.flush();
  }
  else {
    evt->type = LED_EVENT_TYPE_COLOR ;
    evt->value.color.hour = hour ;
    evt->value.color.h = h ;
    evt->value.color.s = s ;
    evt->value.color.v = v ;
    PUSH_EVENT(this->firstLEDEvent, this->lastLEDEvent, evt) ;
  }
}

void CTrunk::add_led_color_event (int16_t *values) {
  LEDEvent evt ;

  if ((evt = (LEDEvent)malloc (sizeof(struct led_event))) == NULL) {
    Serial.print(F("Allocation error\n")) ;
    Serial.flush();
  }
  else {
    evt->type = LED_EVENT_TYPE_COLOR ;
    evt->value.color.hour = *values ;
    evt->value.color.h = *(values+1) ;
    evt->value.color.s = *(values+2) ;
    evt->value.color.v = *(values+3) ;
    PUSH_EVENT(this->firstLEDEvent, this->lastLEDEvent, evt) ;
  }
}

void CTrunk::add_led_wait_event (uint16_t delay_ms) {
  LEDEvent evt ;

  if ((evt = (LEDEvent)malloc (sizeof(struct led_event))) == NULL) {
    Serial.print(F("Allocation error\n")) ;
    Serial.flush();
  }
  else {
    evt->type = LED_EVENT_TYPE_WAIT ;
    evt->value.delay_ms = delay_ms ;
    PUSH_EVENT(this->firstLEDEvent, this->lastLEDEvent, evt) ;
  }
}

static int CTrunk::protothreadBlink(struct pt *pt)
{
  static unsigned long lastTimeBlink = 0 ;
  PT_BEGIN(pt) ;
  while(1) {
    lastTimeBlink = millis() ;
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > this->blink_period_ms) ;
    for (uint8_t i = 0 ; i < NUM_LEDS ; i++) {
      if (this->is_blinking[i]) {
        this->leds[i] = CHSV(this->blinking_colors[i].h, this->blinking_colors[i].s, this->blinking_colors[i].v) ;
      }
    }
    FastLED.show() ;    

    lastTimeBlink = millis() ;
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > this->blink_period_ms) ;
    for (uint8_t i = 0 ; i < NUM_LEDS ; i++) {
      if (this->is_blinking[i]) {
        this->leds[i] = CHSV(this->colors[i].h, this->colors[i].s, this->colors[i].v) ;
      }
    }
    FastLED.show() ;    
  }
  PT_END(pt) ;
}

void CTrunk::run_leds () {
  if (this->firstLEDEvent != NULL) {
    switch (this->firstLEDEvent->type) {
    case LED_EVENT_TYPE_COLOR:
      {
        this->set_led_hsv(this->firstLEDEvent->value.color.hour, this->firstLEDEvent->value.color.h, this->firstLEDEvent->value.color.s, this->firstLEDEvent->value.color.v) ;
      }
      break ;
    case LED_EVENT_TYPE_WAIT:
      {
        delay(this->firstLEDEvent->value.delay_ms) ;
      }
      break ;   
    case LED_EVENT_TYPE_STOP_BLINK:
      {
        uint8_t j = this->firstLEDEvent->value.num - 1;
        this->is_blinking[j] = false ;
        this->set_led_hsv(j+1, this->colors[j].h, this->colors[j].s, this->colors[j].v) ;
      }
      break ;
    case LED_EVENT_TYPE_START_BLINK:
      {
        uint8_t i = this->firstLEDEvent->value.color.hour - 1 ;
        this->blinking_colors[i].h = this->firstLEDEvent->value.color.h ;
        this->blinking_colors[i].s = this->firstLEDEvent->value.color.s ;
        this->blinking_colors[i].v = this->firstLEDEvent->value.color.v ;
        this->is_blinking[i] = true ;
      }
      break ;
    default:
      Serial.print(F("Unknown LED event.")) ;
      Serial.flush();
    }
      POP_EVENT(LEDEvent, this->firstLEDEvent) ;
  }
  this->protothreadBlink(&pt);
}
