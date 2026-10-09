#include "led_strip.hpp"
#include "Branch.hpp"
#include "event_utils.h"

//-- GLOBALS

uint32_t Branch::step_period_us = 1000 ;

//-- METHODS

Branch::Branch ()
  : num(0),
    firstEvent(NULL),
    lastEvent(NULL),
    posCur(0),
    posMax(260),
    maxFailedSteps(5),
    state(STATE_WAIT)
{
  // Nothing
}

Branch::~Branch ()
{
  while (this->firstEvent != NULL) {
    POP_EVENT(MoveEvent, this->firstEvent) ;
  }
}

void Branch::initPins (uint8_t stepPin, uint8_t dirPin, uint8_t speedPin, uint8_t stopPin, uint8_t enablePin)
{
  this->stepPin = stepPin ;
  this->dirPin = dirPin ;
  this->speedPin = speedPin ;
  this->stopPin = stopPin ;
  this->enablePin = enablePin ;
 
  pinMode(this->stepPin, OUTPUT) ;
  pinMode(this->dirPin, OUTPUT) ;
  pinMode(this->speedPin, INPUT_PULLUP) ;
  pinMode(this->stopPin, INPUT_PULLUP) ;
  pinMode(this->enablePin, OUTPUT) ;

#if(DIGITAL_IO_MODE == 2)
  DIGITAL_INIT_OUTPUT_FAST_IO (this->stepPin, this->stepPinOutReg, this->stepPinBitMask) ;
  DIGITAL_INIT_OUTPUT_FAST_IO (this->dirPin, this->dirPinOutReg, this->dirPinBitMask) ;
  DIGITAL_INIT_INPUT_FAST_IO (this->speedPin, this->speedPinInReg, this->speedPinBitMask) ;
  DIGITAL_INIT_INPUT_FAST_IO (this->stopPin, this->stopPinInReg, this->stopPinBitMask) ;
  DIGITAL_INIT_OUTPUT_FAST_IO (this->enablePin, this->enablePinOutReg, this->enablePinBitMask) ;
#endif

  this->disableMotor() ;
  this->posSensorStatePrev = this->speedPinDigitalRead() ;
}

void Branch::addEvent (uint16_t posDest)
{  
  MoveEvent evt ;
  
  if ((evt = (MoveEvent)malloc (sizeof(struct move_event))) == NULL) {
    Serial.print(F("Allocation error\n")) ;
    Serial.flush();
  }
  else { 
    evt->posDest = (posDest > this->posMax) ? this->posMax : posDest ;
    PUSH_EVENT(this->firstEvent, this->lastEvent, evt) ;
  }
}

bool Branch::move ()
{
  static uint32_t count_not_moved = 0;
  //set_led (3, 0, 0, 255) ;     // B
  if (!this->stop() || this->dir == DIR_UP) {
    //set_led (3, 0, 255, 0) ;     // G
    this->stepPinDigitalWrite(HIGH) ;
    delayMicroseconds(Branch::step_period_us) ;
    this->stepPinDigitalWrite(LOW) ;
    delayMicroseconds(Branch::step_period_us) ;
    if (this->arduinoUpdatePos()) {
      count_not_moved = 0 ;
    }
    else {
      count_not_moved++;
    }
  }
  else {
    //set_led (3, 255, 0, 0) ;     // R
    this->posCur = 0 ;
  }
  return count_not_moved < this->maxFailedSteps ;
}

bool Branch::arduinoUpdatePos ()
{
  static bool moved = false ;
  this->posSensorStateNew = this->speedPinDigitalRead() ;

  if (this->posSensorStateNew != this->posSensorStateCur && this->posSensorStateCur == this->posSensorStatePrev) { // && this->posSensorStateCur == this->posSensorStatePrev
    this->posCur += (this->dir == DIR_UP) ? 1 : -1 ;
    moved = true;
  }
  else {
    moved = false;
  }
  
  this->posSensorStatePrev = this->posSensorStateCur ;
  this->posSensorStateCur = this->posSensorStateNew ;

  return moved;
}

void Branch::resetToZeroPosition ()
{
  this->enableMotor() ;
  this->setDirection(this->stop() ? DIR_UP : DIR_DOWN) ;
  this->state = STATE_RESET;
}

void Branch::run ()
{
  static unsigned long time_start, time_end;
  //Serial.print(F("run\n")) ;

  // debug
  //this->move() ;

  if (this->state == STATE_RESET) {
    if ((this->dir == DIR_DOWN && !this->stop()) || (this->dir == DIR_UP && this->stop())) {
      this->move() ;
    }
    else {
      if (this->dir == DIR_UP) {
        this->setDirection(DIR_DOWN) ;
        this->move();
      }
      this->disableMotor() ;
      this->state = STATE_WAIT ;
      this->posCur = 0 ;
      this->end_of_motion();
    }
  }
  else if (this->state == STATE_MOVE) {
    //set_led (2, 255, 255, 0) ; // R G
    //Serial.print(F("state STATE_MOVE\n")) ;
    if (this->posCur != this->firstEvent->posDest) {
      this->move() ;
      //set_led (2, 0, 255, 0) ; // G
    }
    else {
      this->state = STATE_WAIT ;
      time_end = millis();
      //this->showDigitalIOMode();
      printf("Ellapsed time: %ld ms\n", time_end - time_start);
      this->disableMotor() ;
      POP_EVENT(MoveEvent, this->firstEvent) ;
      //set_led (2, 255, 0, 0) ; // R
      this->end_of_motion();
    }
  }
  else if (this->firstEvent != NULL) { // STATE_WAIT and EVENT in stack
    this->state = STATE_MOVE ;
    this->enableMotor() ;
    time_start = millis();
    //Serial.print(F("state WAITING: new event\n")) ;
    set_led (2, 0, 0, 255) ; // B
    this->setDirection((this->posCur < this->firstEvent->posDest) ? DIR_UP : DIR_DOWN) ;
  }

  //Serial.print(F("run end\n")) ;

}
