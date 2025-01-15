/*
 * test.c
 *
 *  Created on: Dec 12, 2023
 *      Author: Ikhtiar Hossain
 */

#include "test.h"
#include "functions.h"

void test_program(void){
	while (1) {
		uint32_t shiftRegisters[] = {0x000000};
		set_led(shiftRegisters);
		//test_led(shiftRegisters);
		//test_pl_switch(shiftRegisters);
		//test_tl_switch(shiftRegisters);
		//pl2_toggle(shiftRegisters, 1000);
		//walk2_red(shiftRegisters);
		//walk2_green(shiftRegisters);
		//vertical_lane_red(shiftRegisters);
		//vertical_lane_orange(shiftRegisters);
		//vertical_lane_green(shiftRegisters);
		test_both_toggle(shiftRegisters);
	}
}

void test_led(uint32_t shiftRegisters[0]) {
	// shiftRegisters[0] = 0x3f3f3f;
	shiftRegisters[0] = (TL2_GREEN | TL4_ORANGE);
	set_led(shiftRegisters);
	HAL_Delay(5000);
}

void test_pl_switch(uint32_t shiftRegisters[0]) {
	if (pl2_switch_on() == true) {
		shiftRegisters[0] = PL2_BLUE;
		set_led(shiftRegisters);
		HAL_Delay(5000);
	}
}

void test_tl_switch(uint32_t shiftRegisters[0]) {
	if (tl4_switch_on() == true) {
		shiftRegisters[0] = PL2_BLUE;
		set_led(shiftRegisters);
		HAL_Delay(5000);
	}
}

void test_both_toggle(uint32_t shiftRegisters[0]) {
	bool pl1 = false;
	bool pl2 = false;
	uint16_t toggleFreq = 300;
	while (1) {
		if (pl1_switch_on() == true) {
			pl1 = true;
		}
		if (pl2_switch_on() == true) {
			pl2 = true;
		}
		if (pl1 == true && pl2 == true) {
			both_toggle(shiftRegisters, toggleFreq);
		}
	}

}
