#ifndef LED_STRIP_HPP
#define LED_STRIP_HPP


//-- DATA STRUCTURES

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

//-- FUNCTIONS

void init_leds() ;

// num : 0  =>  all LEDS
//     : 1..10 => one LED
void set_led_rgb (unsigned char hour, unsigned char r, unsigned char g, unsigned char b) ;
void set_led (unsigned char hour, unsigned char h, unsigned char s, unsigned char v) ;

void set_blink_period_ms (unsigned short period_ms) ;

void add_led_start_blink_event (short int *values) ;

void add_led_stop_blink_event (short int *values) ;

void add_led_color_event (unsigned char hour, unsigned char r, unsigned char g, unsigned char b) ;

void add_led_color_event (short int *values) ;

void add_led_wait_event (unsigned short int delay_ms) ;

void run_leds () ;

#endif /* LED_STRIP_HPP */
