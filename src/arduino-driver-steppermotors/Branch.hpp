#ifndef BRANCH_HPP
#define BRANCH_HPP

// 0: native, 1: fast, 2: fastio
#define DIGITAL_IO_MODE 2

#include <Arduino.h>

#if(DIGITAL_IO_MODE == 1)
#include <digitalWriteFast.h>
#endif

#include "digitalfastio.h"

//-- MACRO CONSTANTS

//-- DATA TYPES

enum STATE { STATE_WAIT, STATE_MOVE, STATE_RESET } ;

enum DIR { DIR_DOWN, DIR_UP } ;

//-- DATA STRUCTURES

typedef struct move_event *MoveEvent ;

struct move_event {   // 4 bytes
  uint16_t posDest ;  // 2 bytes
  MoveEvent next ;    // 2 bytes (pointer)
};

//-- CLASSES

class Branch {

public:

  //== Members

  static uint32_t step_period_us ;

  //== Methods
  
  Branch () ;

  ~Branch () ;
  
  void initPins (uint8_t stepPin, uint8_t dirPin, uint8_t speedPin, uint8_t stopPin, uint8_t enablePin) ;

  void addEvent (uint16_t posDest) ;

  void resetToZeroPosition () ;
  
  void run () ;

  inline void setNumber(uint8_t num)
  {
    this->num = num ;
  }

  inline void setCurPosValue (uint16_t pos) 
  {
    this->posCur = pos ;
  }

  inline void setPosMax (uint16_t pos) 
  {
    this->posMax = pos ;
  }

  inline void setMaxFailedSteps (uint32_t steps) 
  {
    this->maxFailedSteps = steps ;
  }

  inline void sendCurPos()
  {
    Serial.print(F("<j|")) ;
    Serial.print(this->num) ;
    Serial.print(F("|")) ;
    Serial.print(this->posCur) ;
    Serial.print(F(">")) ;
  }
  
protected:

  //== Methods

  bool arduinoUpdatePos () ;
  
  bool move() ;

  inline void showDigitalIOMode()
  {
#if(DIGITAL_IO_MODE == 0)
    Serial.print(F("Arduino\n"));
#elif(DIGITAL_IO_MODE == 1)
    Serial.print(F("Fast\n"));
#else
    Serial.print(F("FastIO\n"));
#endif
  }

  inline void end_of_motion()
  {
    Serial.print(F("<e|")) ;
    Serial.print(this->num) ;
    Serial.print(F(">")) ;
  }

  inline void done()
  {
    Serial.print(F("<d|")) ;
    Serial.print(this->num) ;
    Serial.print(F(">")) ;
  }
  
  inline bool stop ()
  {
    return stopPinDigitalRead() == LOW ;
  }

  inline void setDirection (uint8_t dir)
  {
    this->dir = dir ;
    dirPinDigitalWrite((dir == DIR_UP) ? HIGH : LOW) ;
  }
  
  inline void enableMotor () 
  {
    enablePinDigitalWrite(LOW) ;
  }

  inline void disableMotor ()
  {
    enablePinDigitalWrite(HIGH) ;
  }

  inline void stepPinDigitalWrite (uint8_t val)
  {
#if(DIGITAL_IO_MODE == 0)
    digitalWrite(this->stepPin, val) ;
#elif(DIGITAL_IO_MODE == 1)
    digitalWriteFast(this->stepPin, val) ;
#else
    DIGITAL_WRITE_FAST_IO (this->stepPinOutReg, this->stepPinBitMask, val) ;
#endif
  }

  inline void dirPinDigitalWrite (uint8_t val)
  {
#if(DIGITAL_IO_MODE == 0)
    digitalWrite(this->dirPin, val) ;
#elif(DIGITAL_IO_MODE == 1)
    digitalWriteFast(this->dirPin, val) ;
#else
    DIGITAL_WRITE_FAST_IO (this->dirPinOutReg, this->dirPinBitMask, val) ;
#endif
  }

  inline int speedPinDigitalRead ()
  {
#if(DIGITAL_IO_MODE == 0)
    return digitalRead(this->speedPin) ;
#elif(DIGITAL_IO_MODE == 1)
    return digitalReadFast(this->speedPin) ;
#else
    return DIGITAL_READ_FAST_IO (this->speedPinInReg, this->speedPinBitMask) ;
#endif
  }

  inline int stopPinDigitalRead ()
  {
#if(DIGITAL_IO_MODE == 0)
    return digitalRead(this->stopPin) ;
#elif(DIGITAL_IO_MODE == 1)
    return digitalReadFast(this->stopPin) ;
#else
    return DIGITAL_READ_FAST_IO (this->stopPinInReg, this->stopPinBitMask) ;
#endif
  }

  inline void enablePinDigitalWrite (uint8_t val)
  {
#if(DIGITAL_IO_MODE == 0)
    digitalWrite(this->enablePin, val) ;
#elif(DIGITAL_IO_MODE == 1)
    digitalWriteFast(this->enablePin, val) ;
#else
    DIGITAL_WRITE_FAST_IO (this->enablePinOutReg, this->enablePinBitMask, val) ;
#endif
  }
  
private:

  //== Members

  uint8_t num ;

  MoveEvent firstEvent ;
  MoveEvent lastEvent ;
  
  uint16_t posCur ;
  uint16_t posMax ;
  uint8_t  dir ;

  uint32_t maxFailedSteps ;
  
  uint8_t dirPin ;
  uint8_t stepPin ;
  uint8_t speedPin ;
  uint8_t stopPin ;
  uint8_t enablePin ;

#if(DIGITAL_IO_MODE == 2)

  uint8_t dirPinBitMask ;
  uint8_t stepPinBitMask ;
  uint8_t speedPinBitMask ;
  uint8_t stopPinBitMask ;
  uint8_t enablePinBitMask ;

  volatile uint8_t *dirPinOutReg ;
  volatile uint8_t *stepPinOutReg ;
  volatile uint8_t *speedPinInReg ;
  volatile uint8_t *stopPinInReg ;
  volatile uint8_t *enablePinOutReg ;
  
#endif

  enum STATE state ;
  
  int8_t posSensorStatePrev ;
  int8_t posSensorStateCur ;
  int8_t posSensorStateNew ; 
};

#endif /* BRANCH_HPP */
