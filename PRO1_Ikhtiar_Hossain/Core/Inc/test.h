/*
 * test.h
 *
 *  Created on: Dec 12, 2023
 *      Author: Ikhtiar Hossain
 */

#ifndef INC_TEST_H_
#define INC_TEST_H_

#include "main.h"

void test_program(void);
void test_led(uint32_t shiftRegisters[0]);
void test_pl_switch(uint32_t shiftRegisters[0]);
void test_tl_switch(uint32_t shiftRegisters[0]);
void test_both_toggle(uint32_t shiftRegisters[0]);

#endif /* INC_TEST_H_ */
