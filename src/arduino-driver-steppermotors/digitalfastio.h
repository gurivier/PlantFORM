/* 
 * This C file provides macro-functions to read and write digital pin values
 * of Arduino boards in a faster way than Arduino native functions.
 * 
 * File: digitalfastio.h
 * Author: Guillaume RIVIERE
 * Date: May, 2023
 */

#ifndef DIGITAL_FAST_IO_HPP
#define DIGITAL_FAST_IO_HPP

// Inspired by: https://wolles-elektronikkiste.de/en/logical-operations-and-port-manipulation

// Native functions: /usr/share/arduino/hardware/arduino/avr/cores/arduino/wiring_digital.c

#define DIGITAL_INIT_INPUT_FAST_IO(_PIN, _PIN_IN_REG, _PIN_BIT_MASK)     \
  _PIN_BIT_MASK = digitalPinToBitMask(_PIN) ;                            \
  _PIN_IN_REG = portInputRegister(digitalPinToPort(_PIN)) ;

#define DIGITAL_INIT_OUTPUT_FAST_IO(_PIN, _PIN_OUT_REG, _PIN_BIT_MASK)   \
  _PIN_BIT_MASK = digitalPinToBitMask(_PIN) ;                            \
  _PIN_OUT_REG = portOutputRegister(digitalPinToPort(_PIN)) ;

#define DIGITAL_READ_FAST_IO(_PIN_IN_REG, _PIN_BIT_MASK) (*_PIN_IN_REG & _PIN_BIT_MASK) ? HIGH : LOW

#define DIGITAL_WRITE_FAST_IO(_PIN_OUT_REG, _PIN_BIT_MASK, _VAL)         \
  if (_VAL == LOW) *_PIN_OUT_REG &= ~_PIN_BIT_MASK ;                     \
  else *_PIN_OUT_REG |= _PIN_BIT_MASK ;

#endif /* DIGITAL_FAST_IO_HPP */
