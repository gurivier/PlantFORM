#include <Arduino.h>
#include <digitalWriteFast.h>

#include "Branch.hpp"
#include "led_strip.hpp"
#include "energyshape.hpp"

//-- MACRO CONSTANTS

// Enable printf(): for coding and debugging needs only (0: OFF, 1: ON)
#define ENABLE_PRINTF 1

#define NUM_HOURS  10
#define NUM_MOTORS 10

// Microstepping in: 1, 2, 4, 8, 16
#define MICRO_STEPPING_DEFAULT 16

// Step period
#define STEP_PERIOD_US_DEFAULT 163

// Arduino boards id pins
#define ID1_PIN A5
#define ID2_PIN A4
#define ID3_PIN A3

// High motor pins
#define M0_STEP_PIN    3
#define M0_DIR_PIN     2
#define M0_SPEED_PIN  11
#define M0_STOP_PIN   A0
#define M0_ENABLE_PIN  4

// Low motor pins
#define M1_STEP_PIN    6 
#define M1_DIR_PIN     5 
#define M1_SPEED_PIN  12 
#define M1_STOP_PIN   A1 
#define M1_ENABLE_PIN  7 

// Microstepping pins
#define MS1_PIN 10
#define MS2_PIN  9
#define MS3_PIN  8

//-- MACRO FUNCTIONS

#define IS_LED_BOARD() (arduino_id == 0)
#define IS_MOTOR_BOARD() (arduino_id > 0)
#define IS_THIS_BOARD(_id) (arduino_id == _id)

#if ENABLE_PRINTF
static FILE uartout = {0} ;
static int uart_putchar (char c, FILE *stream) {
  Serial.write(c) ;
  return 0 ;
}
#endif

//-- GLOBALS

Branch branches[2] ; // Two motors (0: above, and 1: below)

uint8_t arduino_id ; // Id of the Arduino board

//-- FUNCTIONS

uint8_t getId (int id1, int id2, int id3)
{
  uint8_t res = 0 ;
  res += (id1 == HIGH) ? 1 : 0 ;  
  res += (id2 == HIGH) ? 2 : 0 ;  
  res += (id3 == HIGH) ? 4 : 0 ;  
  return res ;
}

void ready()
{
  Serial.print(F("<r|")) ;
  Serial.print(arduino_id) ;
  Serial.print(F(">")) ;
}

void set_microstepping (uint8_t mode) 
{
  uint8_t ms1, ms2, ms3 ;
  switch (mode) {
    case 1:
      ms1 = LOW ;
      ms2 = LOW ;
      ms3 = LOW ;
    break;
    case 2:
      ms1 = HIGH ;
      ms2 = LOW ;
      ms3 = LOW ;
    break;
    case 4:
      ms1 = LOW ;
      ms2 = HIGH ;
      ms3 = LOW ;
    break;
    case 8:
      ms1 = HIGH ;
      ms2 = HIGH ;
      ms3 = LOW ;
    break;
    case 16:
      ms1 = HIGH ;
      ms2 = HIGH ;
      ms3 = HIGH ;
    break;
    default:
      Serial.print(F("Unknown mode\n")) ;
      ms1 = HIGH ;
      ms2 = HIGH ;
      ms3 = HIGH ;
  }
  digitalWriteFast(MS1_PIN, ms1) ;
  digitalWriteFast(MS2_PIN, ms2) ;
  digitalWriteFast(MS3_PIN, ms3) ;
}

void set_delay_us (uint32_t delay_us)
{
  Branch::step_period_us = delay_us ;
}

//-- SETUP

void setup ()
{
  Serial.begin(9600) ;

  delay(1000) ;

#if ENABLE_PRINTF
  fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE) ;
  stdout = &uartout ;
#endif

  // Init board id pins

  pinMode(ID1_PIN, OUTPUT) ;
  pinMode(ID2_PIN, OUTPUT) ;
  pinMode(ID3_PIN, OUTPUT) ;

  digitalWriteFast(ID1_PIN, LOW) ;
  digitalWriteFast(ID2_PIN, LOW) ;
  digitalWriteFast(ID3_PIN, LOW) ;

  pinMode(ID1_PIN, INPUT) ;
  pinMode(ID2_PIN, INPUT) ;
  pinMode(ID3_PIN, INPUT) ;

  // Get board id
  arduino_id = getId(digitalReadFast(ID1_PIN), digitalReadFast(ID2_PIN), digitalReadFast(ID3_PIN)) ;

  branches[0].setNumber(arduino_id + arduino_id - 0) ;
  branches[1].setNumber(arduino_id + arduino_id - 1) ;

  // Init board
  if (IS_LED_BOARD()) { // LED board
    init_leds() ;
    energyshape_init();
  }
  else { // Branch boards
    pinMode(MS1_PIN, OUTPUT) ;
    pinMode(MS2_PIN, OUTPUT) ;
    pinMode(MS3_PIN, OUTPUT) ;

    set_delay_us(STEP_PERIOD_US_DEFAULT) ;
    
    set_microstepping(MICRO_STEPPING_DEFAULT) ;

    // motor above
    branches[0].initPins(M0_STEP_PIN, M0_DIR_PIN, M0_SPEED_PIN, M0_STOP_PIN, M0_ENABLE_PIN) ;

    // motor below
    branches[1].initPins(M1_STEP_PIN, M1_DIR_PIN, M1_SPEED_PIN, M1_STOP_PIN, M1_ENABLE_PIN) ;
                     
    // Debugging leds
    init_leds() ;
    set_led_rgb (arduino_id, 0, 0, 255) ;  
  }

  //printf("RX buf: %d (must be 512)\n",  SERIAL_RX_BUFFER_SIZE);
  //printf("Pointer size: %d\n", sizeof(void *));
  //printf("int size: %d\n", sizeof(int));
  //printf("short int size: %d\n", sizeof(short int));
  //printf("long int size: %d\n", sizeof(long int));
  //printf("struct led_color size: %d\n", sizeof(struct led_color));
  //printf("struct move_event size: %d\n", sizeof(struct move_event));
  //printf("struct led_event size: %d\n", sizeof(struct led_event));
  //printf("Enum size: %d (must be 1)\n", sizeof(enum LED_EVENT_TYPE));

}

//-- LOOP

void treat_frame_values (int16_t *values)
{
  //uint8_t hour, h, s, v ;
  static uint8_t num, id ;
  static uint16_t pos_dest, pos ;
  static int16_t *pt_values ;

  //Serial.print(F("treat values\n")) ;

  //printf("%c\n", values[0]) ;
  
  switch (values[0]) {

  case 'b': // blink
   if (IS_LED_BOARD()) {
      Serial.print(F("Must blink")) ;
      add_led_start_blink_event(values+1) ;
   }
  break;

  case 'B':
    if (IS_LED_BOARD()) {
      uint8_t val = values[1] ;
      energyshape_set_brightness(val);
   }
  break;

  case 'e': // end of motion
   if (IS_LED_BOARD()) {
      add_led_stop_blink_event(values+1) ;
   }
  break;

  case 'i': // Get one motor position value
   num = values[1] ;
   id = ((num - 1) * .5) + 1 ;
   if (IS_THIS_BOARD(id)) {
     branches[num % 2].sendCurPos() ;
   }
  break;
  
  case 'p': // Set one motor position value (without moving)
   num = values[1] ;
   id = ((num - 1) * .5) + 1 ;
   if (IS_THIS_BOARD(id)) {
     pos = values[2] ;
     branches[num % 2].setCurPosValue(pos) ;
   }
  break;

  case 'P': // Set all motors position values (without moving)
   if (IS_MOTOR_BOARD()) {
    pt_values = values + arduino_id + arduino_id ;
    // motor above
    //pos_dest = values[arduino_id + arduino_id] ;
    branches[0].setCurPosValue(*pt_values) ;
    // motor below
    //pos_dest = values[(arduino_id + arduino_id) - 1] ;
    branches[1].setCurPosValue(*(pt_values-1)) ;
   }
  break;
 
  case 'l': // Set one LED color (hour 0 => give the color to all LEDs)
    if (IS_LED_BOARD()) {
      //hour = values[1] ;
      //h = values[2] ;
      //s = values[3] ;
      //v = values[4] ;
      //add_led_color_event (hour, h, s, v) ;
      add_led_color_event (values+1) ;
    }
  break;

  case 'g': // Set one LED color (hour 0 => give the color to all LEDs)
    if (IS_LED_BOARD()) {
      energyshape_set_gain (values[1]) ;
    }
  break;

  case 'w': // Sleep LEDs event
    if (IS_LED_BOARD()) {
      add_led_wait_event (values[1]) ;
    }
  break;
  
  case 'L': // Set all LEDs colors from vector
    if (IS_LED_BOARD()) {
      for (uint8_t j=0 ; j < NUM_HOURS ; j++) {
        //hour = j+1 ;
        //h = values[3*j+1] ;
        //s = values[3*j+2] ;
        //v = values[3*j+3] ;
        //printf ("hour = %d\n", hour) ;
        //add_led_color_event (hour, h, s, v) ;
        pt_values = values+j+j+j+1 ;
        add_led_color_event (j+1, *pt_values, *(pt_values+1), *(pt_values+2)) ;
      }
    }
  break;
  
  case 'm': // Move one motor
     num = values[1] ;
     id = ((num - 1)  * .5) + 1 ;
     if (IS_THIS_BOARD(id)) {
       pos_dest = values[2] ;
       branches[num % 2].addEvent(pos_dest) ; // 0: motor above, 1: motor below
       //set_led_rgb (0, 0, 0, 0) ;  
       set_led_rgb (1, 0, 255, 0) ;    
     }
  break;
  
  case 'M': // Move all motors
    if (IS_MOTOR_BOARD()) {
      pt_values = values + arduino_id + arduino_id ;
      // motor above
      //pos_dest = values[arduino_id + arduino_id] ;
      branches[0].setCurPosValue(*pt_values) ;
      // motor below
      //pos_dest = values[(arduino_id + arduino_id) - 1] ;
      branches[1].setCurPosValue(*(pt_values-1)) ;
      //set_led_rgb (0, 0, 0, 0) ;  
      //set_led_rgb (1, 0, 255, 0) ;    
    }
  break;
  
  case 'c': // Set one LED color & move one motor (couple)
    if (IS_LED_BOARD()) {
      //hour = values[1] ;
      //h = values[3] ;
      //s = values[4] ;
      //v = values[5] ;
      //add_led_color_event (hour, h, s, v) ;
      add_led_color_event (values+1) ;
    }
    else { // motor board
     num = values[1] ;
     id = ((num - 1)  * .5) + 1 ;
     if (IS_THIS_BOARD(id)) {
       num = values[1] ;
       pos_dest = values[2] ;
       branches[num % 2].addEvent(pos_dest) ; // 0: motor above, 1: motor below
       //set_led_rgb (0, 0, 0, 0) ;  
       set_led_rgb (1, 0, 255, 0) ;
     }
    }
  break;
  
  case 'C': // Set all LEDs colors from vector & move motors from vector (couples)
     if (IS_LED_BOARD()) {
      for (uint8_t j = 1 ; j <= NUM_HOURS ; j += 3) {
        //hour = j ;
        //h = values[NUM_MOTORS + j] ;
        //s = values[NUM_MOTORS + j+1] ;
        //v = values[NUM_MOTORS + j+2] ;
        //add_led_event (hour, h, s, v) ;
        pt_values = values + NUM_MOTORS + j ;
        add_led_color_event (j, *pt_values, *(pt_values+1), *(pt_values+2)) ;
      }
    }
    else { // motor board
      pt_values = values + arduino_id + arduino_id ;
      // motor above
      //pos_dest = values[arduino_id + arduino_id] ;
      branches[0].setCurPosValue(*pt_values) ;
      // motor below
      //pos_dest = values[(arduino_id + arduino_id) - 1] ;
      branches[1].setCurPosValue(*(pt_values-1)) ;
      //set_led_rgb (0, 0, 0, 0) ;  
      set_led_rgb (1, 0, 255, 0) ;   
    }
  break;

  case 'z': // Reset one motor to zero position
    if (IS_MOTOR_BOARD()) {
      num = values[1] ;
      id = ((num - 1)  * .5) + 1 ;
      if (IS_THIS_BOARD(id)) {
        branches[num % 2].resetToZeroPosition() ;
      }
    }
  break;
  
  case 'Z': // Reset all motors to zero position
    if (IS_MOTOR_BOARD()) {
      branches[0].resetToZeroPosition() ;
      branches[1].resetToZeroPosition() ;
    }
  break;
  
  case 'D': // steppers delay in nanoseconds
    if (IS_MOTOR_BOARD()) {
      set_delay_us(values[1]) ;
    }
  break;
  
  case 'S': // micro-steppring
    if (IS_MOTOR_BOARD()) {
      set_microstepping(values[1]) ;
    }
  break;

  case 'F': // max failed steps
    if (IS_MOTOR_BOARD()) {
      branches[0].setMaxFailedSteps(values[1]) ;
      branches[1].setMaxFailedSteps(values[1]) ;
    }
  break;

  case 'X': // pos max
    if (IS_MOTOR_BOARD()) {
      branches[0].setPosMax(values[1]) ;
      branches[1].setPosMax(values[1]) ;
    }
  break;

  case 'K': // pos max
    if (IS_LED_BOARD()) {
      set_blink_period_ms(values[1]) ;
    }
  break;
    
  default:
    Serial.print(F("Unknown letter:")) ;
    Serial.print(values[0]) ;
    Serial.print(F("\n")) ;
  } 
}

void receive_frame_from_serial_and_treat_values ()
{
  static int16_t values[50], *pt_values ;
  //static uint8_t i ;
  static uint8_t b ;
  static int8_t sign ;
  static uint16_t val ;
  //static char buf[256] ;
  //static char *pbuf ;
  static bool is_reading = false ;
  
  //Serial.print(F("find first char\n")) ;

  if (!is_reading) {
    // Seek start
    //while ((b = Serial.read()) != '<') ;
    if ((b = Serial.read()) == '<') {
      is_reading = true ;
      //pbuf = buf ;
      //*pbuf++ = '<' ;
      Serial.print('<');
      //i = 0 ;
      pt_values = values ;
      sign = 1 ;
      val = 0 ;
      //set_led_rgb (3, 0, 0, 255) ; 
    }
  }
  else {
    //Serial.print(F("find next chars\n")) ;

    //set_led_rgb (4, 0, 0, 255) ;
    
    // Read values
    if ((b = Serial.read()) != '>') {
      Serial.write(b);
      if (b == '<') {
        //pbuf = buf ;
        //*pbuf++ = '<' ;
        //i = 0 ;
        pt_values = values ;
        sign = 1 ;
        val = 0 ;
      }
      else if (b == '|') {
        //*pbuf++ = '|' ;
        //i++ ;
        pt_values++ ;
        sign = 1 ;
        val = 0 ;
      }
      else if (b == '-') {
        //*pbuf++ = '-' ;
        sign = -1 ;
      }
      else if ((b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z')) {
        //*pbuf++ = b ;
        //values[i] = b ;
        *pt_values = b ;
      }
      else if (b >= '0' && b <= '9') {
        //*pbuf++ = b ;
        val *= 10 ;
        val += b - '0' ;
        //values[i] = sign * val ;
        *pt_values = sign * val ;
        //printf("b=%c val=%d\n", b, val) ;
      }
    }
    else {
      //*pbuf++ = '>' ;
      //*pbuf++ = '\0' ;
      is_reading = false ;

      // Send to next board
      Serial.print('>');
      //Serial.println(buf) ;

      //printf("arduino_id=%d\n", arduino_id) ;
      //printf("id=%d\n", values[0]) ;
      //set_led_rgb (values[0], 255, 0, 0) ; 

      //set_led_rgb (5, 0, 0, 255) ; 

      //Serial.print(F("ready to treat\n")) ;
    
      // Treatment
      treat_frame_values(values) ;
    }
  }
}

void loop ()
{
  //== RECEIVING
  
  if (Serial.available() > 0) {
    //set_led_rgb (2, 0, 0, 255) ;
    //set_led_rgb (10, 0, 0, 255) ;   
    //delayMicroseconds(10000);
    receive_frame_from_serial_and_treat_values() ;
  }
  
  //== RUN
  
  if (IS_MOTOR_BOARD()) {
    branches[0].run() ;
    branches[1].run() ;
  }
  else {
    run_leds() ;
  }
  
  //Serial.print(F("loop end\n")) ;
}
