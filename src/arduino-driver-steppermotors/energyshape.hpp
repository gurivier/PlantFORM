#ifndef ENERGYSHAPE_HPP
#define ENERGYSHAPE_HPP

void energyshape_init();

void energyshape_set_brightness(unsigned char value) ; /* value in [0 ; 255] */

void energyshape_set_gain(char value); /* value in [-10 ; +10] + 32 + 64 */

#endif /* ENERGYSHAPE_HPP */
