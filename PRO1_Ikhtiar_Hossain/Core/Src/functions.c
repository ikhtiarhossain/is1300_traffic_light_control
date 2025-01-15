/*
 * functions.c
 *
 *  Created on: Dec 12, 2023
 *      Author: Ikhtiar Hossain
 */

#include "functions.h"
#include <spi.h>

// handle the shift registers with spi3 to control the lights
void set_led(uint32_t shiftRegisters[]) {
	HAL_SPI_Transmit(&hspi3, shiftRegisters, 3, 1);

	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
}

bool pl1_switch_on(void) {
	if (HAL_GPIO_ReadPin(PL1_Switch_GPIO_Port, PL1_Switch_Pin) == 0) {
		return true;
	} else {
		return false;
	}
}
bool pl2_switch_on(void) {
	if (HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == 0) {
		return true;
	} else {
		return false;
	}
}

bool tl1_switch_on(void) {
	if (HAL_GPIO_ReadPin(TL1_Car_GPIO_Port, TL1_Car_Pin) == 0) {
		return true;
	} else {
		return false;
	}
}

bool tl2_switch_on(void) {
	if (HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin) == 0) {
		return true;
	} else {
		return false;
	}
}

bool tl3_switch_on(void) {
	if (HAL_GPIO_ReadPin(TL3_Car_GPIO_Port, TL3_Car_Pin) == 0) {
		return true;
	} else {
		return false;
	}
}

bool tl4_switch_on(void) {
	if (HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin) == 0) {
		return true;
	} else {
		return false;
	}
}

void pl1_toggle(uint32_t shiftRegisters[0], uint16_t toggleFreq) {
	shiftRegisters[0] |= PL1_BLUE;
	set_led(shiftRegisters);
	HAL_Delay(toggleFreq);
	shiftRegisters[0] &= ~(PL1_BLUE);
	set_led(shiftRegisters);
	HAL_Delay(toggleFreq);
}

void pl2_toggle(uint32_t shiftRegisters[0], uint16_t toggleFreq) {
	shiftRegisters[0] |= PL2_BLUE;
	set_led(shiftRegisters);
	HAL_Delay(toggleFreq);
	shiftRegisters[0] &= ~(PL2_BLUE);
	set_led(shiftRegisters);
	HAL_Delay(toggleFreq);
}

void both_toggle(uint32_t shiftRegisters[0], uint16_t toggleFreq) {
	shiftRegisters[0] |= PL1_BLUE;
	shiftRegisters[0] |= PL2_BLUE;
	set_led(shiftRegisters);
	HAL_Delay(toggleFreq);
	shiftRegisters[0] &= ~(PL1_BLUE);
	shiftRegisters[0] &= ~(PL2_BLUE);
	set_led(shiftRegisters);
	HAL_Delay(toggleFreq);
}
void walk1_red(uint32_t shiftRegisters[0]) {
	shiftRegisters[0] |= PL1_RED;
	shiftRegisters[0] &= ~(PL1_GREEN);
	set_led(shiftRegisters);
}

void walk1_green(uint32_t shiftRegisters[0]) {
	shiftRegisters[0] |= PL1_GREEN;
	shiftRegisters[0] &= ~(PL1_RED);
	set_led(shiftRegisters);
}

void walk2_red(uint32_t shiftRegisters[0]) {
	shiftRegisters[0] |= PL2_RED;
	shiftRegisters[0] &= ~(PL2_GREEN);
	set_led(shiftRegisters);
}


void walk2_green(uint32_t shiftRegisters[0]) {
	shiftRegisters[0] |= PL2_GREEN;
	shiftRegisters[0] &= ~(PL2_RED);
	set_led(shiftRegisters);
}

void vertical_lane_red(uint32_t shiftRegisters[0]) {
	shiftRegisters[0] |= TL4_RED;
	shiftRegisters[0] |= TL2_RED;
	shiftRegisters[0] &= ~(TL4_GREEN);
	shiftRegisters[0] &= ~(TL2_GREEN);
	shiftRegisters[0] &= ~(TL4_ORANGE);
	shiftRegisters[0] &= ~(TL2_ORANGE);
	set_led(shiftRegisters);
}

void vertical_lane_orange(uint32_t shiftRegisters[0]) {
	shiftRegisters[0] |= TL4_ORANGE;
	shiftRegisters[0] |= TL2_ORANGE;
	shiftRegisters[0] &= ~(TL4_GREEN);
	shiftRegisters[0] &= ~(TL2_GREEN);
	shiftRegisters[0] &= ~(TL4_RED);
	shiftRegisters[0] &= ~(TL2_RED);
	set_led(shiftRegisters);
}

void vertical_lane_green(uint32_t shiftRegisters[0]) {
	shiftRegisters[0] |= TL4_GREEN;
	shiftRegisters[0] |= TL2_GREEN;
	shiftRegisters[0] &= ~(TL4_RED);
	shiftRegisters[0] &= ~(TL2_RED);
	shiftRegisters[0] &= ~(TL4_ORANGE);
	shiftRegisters[0] &= ~(TL2_ORANGE);
	set_led(shiftRegisters);
}

void horizontal_lane_red(uint32_t shiftRegisters[0]) {
	shiftRegisters[0] |= TL1_RED;
	shiftRegisters[0] |= TL3_RED;
	shiftRegisters[0] &= ~(TL1_GREEN);
	shiftRegisters[0] &= ~(TL3_GREEN);
	shiftRegisters[0] &= ~(TL1_ORANGE);
	shiftRegisters[0] &= ~(TL3_ORANGE);
	set_led(shiftRegisters);
}

void horizontal_lane_orange(uint32_t shiftRegisters[0]) {
	shiftRegisters[0] |= TL1_ORANGE;
	shiftRegisters[0] |= TL3_ORANGE;
	shiftRegisters[0] &= ~(TL1_GREEN);
	shiftRegisters[0] &= ~(TL3_GREEN);
	shiftRegisters[0] &= ~(TL1_RED);
	shiftRegisters[0] &= ~(TL3_RED);
	set_led(shiftRegisters);
}

void horizontal_lane_green(uint32_t shiftRegisters[0]) {
	shiftRegisters[0] |= TL1_GREEN;
	shiftRegisters[0] |= TL3_GREEN;
	shiftRegisters[0] &= ~(TL1_RED);
	shiftRegisters[0] &= ~(TL3_RED);
	shiftRegisters[0] &= ~(TL1_ORANGE);
	shiftRegisters[0] &= ~(TL3_ORANGE);
	set_led(shiftRegisters);
}

void pl1_delay(uint32_t shiftRegisters[0], uint16_t toggleFreq, uint16_t pedestrianDelay, uint16_t orangeDelay) {
	uint32_t toggleTime = HAL_GetTick();
	while ((HAL_GetTick() - toggleTime) < pedestrianDelay) {
		pl1_toggle(shiftRegisters, toggleFreq);
		if((HAL_GetTick() - toggleTime) > (pedestrianDelay - orangeDelay)) {
			horizontal_lane_orange(shiftRegisters);
			vertical_lane_orange(shiftRegisters);
			walk1_red(shiftRegisters);
			walk2_red(shiftRegisters);
		}
	}
}

void pl2_delay(uint32_t shiftRegisters[0], uint16_t toggleFreq, uint16_t pedestrianDelay, uint16_t orangeDelay) {
	uint32_t toggleTime = HAL_GetTick();
	while ((HAL_GetTick() - toggleTime) < pedestrianDelay) {
		pl2_toggle(shiftRegisters, toggleFreq);
		if((HAL_GetTick() - toggleTime) > (pedestrianDelay - orangeDelay)) {
			vertical_lane_orange(shiftRegisters);
			horizontal_lane_orange(shiftRegisters);
			walk1_red(shiftRegisters);
			walk2_red(shiftRegisters);
		}
	}
}

bool v_cars(void){
	if (tl2_switch_on() == true || tl4_switch_on() == true) {
		return true;
	} else {
		return false;
	}
}

bool h_cars(void){
	if (tl1_switch_on() == true || tl3_switch_on() == true) {
		return true;
	} else {
		return false;
	}
}

