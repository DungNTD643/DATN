/*
 * PTO.c
 *
 *  Created on: Apr 19, 2025
 *      Author: Admin
 */

#include "PTO.h"

static alt_u8 a1 = 0;
static alt_u8 a0 = 0;

void PTO_run(MOTOR_t *user_config){
	if((user_config->motor_ID) == 0){
		if(a0){
			while(!IORD(DRIVER1_0_BASE, 0));
			IOWR(DRIVER1_0_BASE, 0, 0);
			IOWR(DRIVER1_0_BASE, 0, 1);
		}
		else{
			IOWR(DRIVER1_0_BASE, 0, 1);
			a0++;
		}
	}
	else if((user_config->motor_ID) == 1){
		if(a1){
			while(!IORD(DRIVER1_1_BASE, 0));
			IOWR(DRIVER1_1_BASE, 0, 0);
			IOWR(DRIVER1_1_BASE, 0, 1);
		}
		else{
			IOWR(DRIVER1_1_BASE, 0, 1);
			a1++;
		}
	}
}


void PTO_config(MOTOR_t *user_config){

	if((user_config->motor_ID) == 0){
		if(a0){
			while(!IORD(DRIVER1_0_BASE, 0));
		}
		IOWR(DRIVER1_0_BASE, 1, start_degree * pulse_per_degree);
		IOWR(DRIVER1_0_BASE, 2, (user_config->rotate_degree - start_degree) * pulse_per_degree);
		IOWR(DRIVER1_0_BASE, 3, user_config->rotate_degree * pulse_per_degree);
		IOWR(DRIVER1_0_BASE, 4, user_config->direction);
	}
	else if((user_config->motor_ID) == 1){
		if(a1){
			while(!IORD(DRIVER1_1_BASE, 0));
		}
		IOWR(DRIVER1_1_BASE, 1, start_degree * pulse_per_degree);
		IOWR(DRIVER1_1_BASE, 2, (user_config->rotate_degree - start_degree) * pulse_per_degree);
		IOWR(DRIVER1_1_BASE, 3, user_config->rotate_degree * pulse_per_degree);
		IOWR(DRIVER1_1_BASE, 4, user_config->direction);
	}
}

void PTO_Innit(){
	IOWR(DRIVER1_0_BASE, 5, 250);	//period_max_us
	IOWR(DRIVER1_0_BASE, 6, 150);	//period_min_us
	IOWR(DRIVER1_0_BASE, 7, 2);		//us
	IOWR(DRIVER1_0_BASE, 8, 5000);	//T_hold_us

	IOWR(DRIVER1_1_BASE, 5, 250);	//period_max_us
	IOWR(DRIVER1_1_BASE, 6, 150);	//period_min_us
	IOWR(DRIVER1_1_BASE, 7, 2);		//us
	IOWR(DRIVER1_1_BASE, 8, 5000);	//T_hold_us
}
