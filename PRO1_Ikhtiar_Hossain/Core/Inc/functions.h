/*
 * functions.h
 *
 *  Created on: Dec 12, 2023
 *      Author: Ikhtiar Hossain
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

#include "main.h"
#include <stdbool.h>

// all the led shift register bit addresses defined
// first shift register
#define TL1_RED 0x10000
#define TL1_ORANGE 0x20000
#define TL1_GREEN 0x40000
#define PL1_RED 0x80000
#define PL1_GREEN 0x100000
#define PL1_BLUE 0x200000
// second shift register
#define TL2_RED 0x100
#define TL2_ORANGE 0x200
#define TL2_GREEN 0x400
#define PL2_RED 0x800
#define PL2_GREEN 0x1000
#define PL2_BLUE 0x2000
// third shift register
#define TL3_RED 0x1
#define TL3_ORANGE 0x2
#define TL3_GREEN 0x4
#define TL4_RED 0x8
#define TL4_ORANGE 0x10
#define TL4_GREEN 0x20

void set_led(uint32_t shiftRegisters[]);
bool pl1_switch_on(void);
bool pl2_switch_on(void);

bool tl1_switch_on(void);
bool tl2_switch_on(void);
bool tl3_switch_on(void);
bool tl4_switch_on(void);

void pl1_toggle(uint32_t shiftRegisters[0], uint16_t toggleFreq);
void pl2_toggle(uint32_t shiftRegisters[0], uint16_t toggleFreq);
void both_toggle(uint32_t shiftRegisters[0], uint16_t toggleFreq);

void walk1_red(uint32_t shiftRegisters[0]);
void walk1_green(uint32_t shiftRegisters[0]);
void walk2_red(uint32_t shiftRegisters[0]);
void walk2_green(uint32_t shiftRegisters[0]);

void vertical_lane_red(uint32_t shiftRegisters[0]);
void vertical_lane_orange(uint32_t shiftRegisters[0]);
void vertical_lane_green(uint32_t shiftRegisters[0]);
void horizontal_lane_red(uint32_t shiftRegisters[0]);
void horizontal_lane_orange(uint32_t shiftRegisters[0]);
void horizontal_lane_green(uint32_t shiftRegisters[0]);

void pl1_delay(uint32_t shiftRegisters[0], uint16_t toggleFreq, uint16_t pedestrianDelay, uint16_t orangeDelay);
void pl2_delay(uint32_t shiftRegisters[0], uint16_t toggleFreq, uint16_t pedestrianDelay, uint16_t orangeDelay);

bool v_cars(void);
bool h_cars(void);

#endif /* INC_FUNCTIONS_H_ */
