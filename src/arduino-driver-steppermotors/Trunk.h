#ifndef LED_STRIP_HPP
#define LED_STRIP_HPP

#include <Arduino.h>

#include <FastLED.h>//https://github.com/FastLED/FastLED

#include <pt.h>// ProtoThreads

//-- Macro Constants

#define NUM_LEDS 10

//-- Data Structures

typedef struct HSV {
  unsigned char h, s, v ;
} HSV ;

enum LED_EVENT_TYPE { LED_EVENT_TYPE_WAIT, LED_EVENT_TYPE_COLOR, LED_EVENT_TYPE_START_BLINK, LED_EVENT_TYPE_STOP_BLINK } ;

typedef struct led_event *LEDEvent;

struct led_color {        // 4 bytes
  unsigned char hour ;    // 1 byte
  unsigned char h, s, v ; // 3 bytes
};

struct led_event {                 // 7 bytes
  enum LED_EVENT_TYPE type ;       // 1 byte
  union {
    unsigned short int delay_ms ;  // 2 bytes
    struct led_color color ;       // 4 bytes
    unsigned char num ;            // 1 byte
  } value ;
  LEDEvent next ;                  // 2 bytes (pointer)
};

//-- Class

class CTrunk {

public:

  CTrunk() ;
  
  void init_leds() ;

  // num : 0  =>  all LEDS
  //     : 1..10 => one LED
  void set_led_rgb (uint8_t hour, uint8_t r, uint8_t g, uint8_t b) ;
  void set_led_hsv (uint8_t hour, uint8_t h, uint8_t s, uint8_t v) ;

  void set_blink_period_ms (uint16_t period_ms) ;

  void add_led_start_blink_event (int16_t *values) ;

  void add_led_stop_blink_event (int16_t *values) ;

  void add_led_color_event (uint8_t hour, uint8_t r, uint8_t g, uint8_t b) ;

  void add_led_color_event (int16_t *values) ;

  void add_led_wait_event (uint16_t delay_ms) ;

  void run () ;

protected:

  int CTrunk::protothreadBlink(struct pt *pt);

private:

  struct pt m_pt ;
  
  uint16_t m_blink_period_ms = 400 ;

  HSV m_colors[NUM_LEDS] ;
  HSV m_blinking_colors[NUM_LEDS] ;
  bool m_is_blinking[NUM_LEDS] ;

  CRGB m_leds[NUM_LEDS] ;

  LEDEvent m_firstLEDEvent = NULL ;
  LEDEvent m_lastLEDEvent = NULL ;
};

//-- Objects

extern CTrunk Trunk;

#endif /* LED_STRIP_HPP */
