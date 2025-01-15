/*
 * main_program.c
 *
 *  Created on: Dec 14, 2023
 *      Author: Ikhtiar Hossain
 */

#include "main_program.h"
#include "functions.h"

const uint16_t toggleFreq = 300;
const uint16_t pedestrianDelay = 3000;
const uint16_t walkingDelay = 7000;
const uint16_t orangeDelay = 2000;
const uint16_t greenDelay = 6000;
const uint16_t redDelayMax = 12000;


//define state machine
typedef enum {
	V_LANE, H_LANE, CROSS_1, CROSS_2, SWAP_LANE
} States;

States state, next_state, prev_lane_state;

void main_program(void) {
	uint32_t shiftRegisters[] = {0x000000};
	set_led(shiftRegisters);
	uint32_t counter;
	bool pl1Pressed = false;
	bool pl2Pressed = false;

	while(1) {

		state = next_state;
		switch (state) {
		case V_LANE:
			vertical_lane_green(shiftRegisters);
			horizontal_lane_red(shiftRegisters);
			walk1_green(shiftRegisters);
			walk2_red(shiftRegisters);

			if (pl1Pressed == true) {
				prev_lane_state = V_LANE;
				next_state = CROSS_1;
				break;
			}
			if (pl2Pressed == true) {
				prev_lane_state = V_LANE;
				next_state = CROSS_2;
				break;
			}

			if (v_cars() == false && h_cars() == true) {
				prev_lane_state = V_LANE;
				next_state = SWAP_LANE;
				break;
			}

			if (v_cars() == false && h_cars() == false) {
				counter = HAL_GetTick();
				while ( (HAL_GetTick() - counter) < greenDelay) {
					if (v_cars() == true || h_cars() == true || pl2_switch_on() == true) {
						break;
					}
				}
				prev_lane_state = V_LANE;
				next_state = SWAP_LANE;
			}

			if (v_cars() == true && h_cars() == true) {
				counter = HAL_GetTick();
				while ( (HAL_GetTick() - counter) < redDelayMax) {
					if (pl2_switch_on() == true) {
						break;
					}
				}
				prev_lane_state = V_LANE;
				next_state = SWAP_LANE;
			}


			if (pl2_switch_on() == true) {
				pl2Pressed = true;
				prev_lane_state = V_LANE;
				next_state = CROSS_2;
				break;
			}

			if (v_cars() == true && h_cars() == false) {
				next_state = V_LANE;
			}

			break;

		case H_LANE:
			horizontal_lane_green(shiftRegisters);
			vertical_lane_red(shiftRegisters);
			walk1_red(shiftRegisters);
			walk2_green(shiftRegisters);

			if (pl2Pressed == true) {
				prev_lane_state = H_LANE;
				next_state = CROSS_2;
				break;
			}
			if (pl1Pressed == true) {
				prev_lane_state = H_LANE;
				next_state = CROSS_1;
				break;
			}

			if (h_cars() == false && v_cars() == true) {
				prev_lane_state = H_LANE;
				next_state = SWAP_LANE;
				break;
			}

			if (h_cars() == false && v_cars() == false) {
				counter = HAL_GetTick();
				while ( (HAL_GetTick() - counter) < greenDelay) {
					if (v_cars() == true || h_cars() == true || pl1_switch_on() == true) {
						break;
					}
				}
				prev_lane_state = H_LANE;
				next_state = SWAP_LANE;
			}

			if (h_cars() == true && v_cars() == true) {
				counter = HAL_GetTick();
				while ( (HAL_GetTick() - counter) < redDelayMax) {
					if (pl1_switch_on() == true) {
						break;
					}
				}
				prev_lane_state = H_LANE;
				next_state = SWAP_LANE;
			}

			if (pl1_switch_on() == true) {
				pl1Pressed = true;
				prev_lane_state = H_LANE;
				next_state = CROSS_1;
				break;
			}

			if (h_cars() == true && v_cars() == false) {
				next_state = H_LANE;
			}

			break;

		case CROSS_1:
			counter = HAL_GetTick();
			while ((HAL_GetTick() - counter) < pedestrianDelay) {
				if (pl2Pressed == true) {
					both_toggle(shiftRegisters, toggleFreq);
				} else {
					pl1_toggle(shiftRegisters, toggleFreq);
				}

				if((HAL_GetTick() - counter) > (pedestrianDelay - orangeDelay)) {
					horizontal_lane_orange(shiftRegisters);
					vertical_lane_orange(shiftRegisters);
					walk1_red(shiftRegisters);
					walk2_red(shiftRegisters);

					if (pl2_switch_on() == true) {
						pl2Pressed = true;
					}
				}
			}

			counter = HAL_GetTick();
			while ((HAL_GetTick() - counter) < walkingDelay) {
				vertical_lane_green(shiftRegisters);
				horizontal_lane_red(shiftRegisters);
				walk1_green(shiftRegisters);
				walk2_red(shiftRegisters);

				if (pl2_switch_on() == true) {
					pl2Pressed = true;
				}
				if (pl2Pressed == true) {
					pl2_toggle(shiftRegisters, toggleFreq);
				}
			}
			pl1Pressed = false;

			counter = HAL_GetTick();
			while ((HAL_GetTick() - counter) < orangeDelay) {
				vertical_lane_orange(shiftRegisters);
				horizontal_lane_orange(shiftRegisters);
				walk1_red(shiftRegisters);
				walk2_red(shiftRegisters);

				if (pl1_switch_on() == true) {
					pl1Pressed = true;
				}
				if (pl2_switch_on() == true) {
					pl2Pressed = true;
				}

				if (pl1Pressed == true && pl2Pressed == true) {
					both_toggle(shiftRegisters, toggleFreq);
				} else if (pl1Pressed == true) {
					pl1_toggle(shiftRegisters, toggleFreq);
				} else if (pl2Pressed == true) {
					pl2_toggle(shiftRegisters, toggleFreq);
				}
			}
			next_state = H_LANE;

			break;

		case CROSS_2:
			counter = HAL_GetTick();
			while ((HAL_GetTick() - counter) < pedestrianDelay) {
				if (pl1Pressed == true) {
					both_toggle(shiftRegisters, toggleFreq);
				} else {
					pl2_toggle(shiftRegisters, toggleFreq);
				}

				if((HAL_GetTick() - counter) > (pedestrianDelay - orangeDelay)) {
					horizontal_lane_orange(shiftRegisters);
					vertical_lane_orange(shiftRegisters);
					walk1_red(shiftRegisters);
					walk2_red(shiftRegisters);

					if (pl1_switch_on() == true) {
						pl1Pressed = true;
					}
				}
			}

			counter = HAL_GetTick();
			while ((HAL_GetTick() - counter) < walkingDelay) {
				vertical_lane_red(shiftRegisters);
				horizontal_lane_green(shiftRegisters);
				walk1_red(shiftRegisters);
				walk2_green(shiftRegisters);

				if (pl1_switch_on() == true) {
					pl1Pressed = true;
				}
				if (pl1Pressed == true) {
					pl1_toggle(shiftRegisters, toggleFreq);
				}
			}
			pl2Pressed = false;

			counter = HAL_GetTick();
			while ((HAL_GetTick() - counter) < orangeDelay) {
				vertical_lane_orange(shiftRegisters);
				horizontal_lane_orange(shiftRegisters);
				walk1_red(shiftRegisters);
				walk2_red(shiftRegisters);

				if (pl1_switch_on() == true) {
					pl1Pressed = true;
				}
				if (pl2_switch_on() == true) {
					pl2Pressed = true;
				}

				if (pl1Pressed == true && pl2Pressed == true) {
					both_toggle(shiftRegisters, toggleFreq);
				} else if (pl1Pressed == true) {
					pl1_toggle(shiftRegisters, toggleFreq);
				} else if (pl2Pressed == true) {
					pl2_toggle(shiftRegisters, toggleFreq);
				}
			}
			next_state = V_LANE;

			break;

		case SWAP_LANE:
			counter = HAL_GetTick();
			while ((HAL_GetTick() - counter) < orangeDelay) {
				vertical_lane_orange(shiftRegisters);
				horizontal_lane_orange(shiftRegisters);
				walk1_red(shiftRegisters);
				walk2_red(shiftRegisters);

				if (pl1_switch_on() == true) {
					pl1Pressed = true;
				}
				if (pl2_switch_on() == true) {
					pl2Pressed = true;
				}

				if (pl1Pressed == true && pl2Pressed == true) {
					both_toggle(shiftRegisters, toggleFreq);
				} else if (pl1Pressed == true) {
					pl1_toggle(shiftRegisters, toggleFreq);
				} else if (pl2Pressed == true) {
					pl2_toggle(shiftRegisters, toggleFreq);
				}
			}

			if (prev_lane_state == V_LANE) {
				next_state = H_LANE;
			} else {
				next_state = V_LANE;
			}

			break;
		}
	}
}

/* task 1 only

//define state machine
typedef enum {
	V_LANE, CROSS_2
} States;

States state, next_state;

void main_program(void) {
	uint32_t shiftRegisters[] = {0x000000};
	set_led(shiftRegisters);

	while(1) {

		state = next_state;
		switch (state) {
		case V_LANE:
			vertical_lane_green(shiftRegisters);
			walk2_red(shiftRegisters);

			if (pl2_switch_on() == true) {
				next_state = CROSS_2;
			}

			break;

		case CROSS_2:
			pl2_delay(shiftRegisters, toggleFreq, pedestrianDelay, orangeDelay);
			vertical_lane_red(shiftRegisters);
			walk2_green(shiftRegisters);

			HAL_Delay(walkingDelay);
			vertical_lane_orange(shiftRegisters);
			walk2_red(shiftRegisters);
			HAL_Delay(orangeDelay);
			next_state = V_LANE;
			break;
		}
	}
}
*/
