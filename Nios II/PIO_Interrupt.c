/*
 * PIO_Interrupt.c
 *
 *  Created on: Jun 4, 2025
 *      Author: Admin
 */
#include "PIO_Interrupt.h"
int off_set[3];
alt_u8 i;
void pio_input_0_isr(void* context, alt_u32 id) {
	for(i = 0; i < 3; i++){
		off_set[i] = motor_angle[i];
	}
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_0_BASE, 0);
}

void init_pio_0_input_interrupt(){
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_0_BASE, 0);
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_0_BASE, 0x1);
    alt_ic_isr_register(
    	PIO_0_IRQ_INTERRUPT_CONTROLLER_ID,
		PIO_0_IRQ,
        pio_input_0_isr,
        NULL,
        NULL
    );
}

void pio_input_1_isr(void* context, alt_u32 id) {
	if(off_set[0] == 0 && off_set[1] == 0 && off_set[2] == 0){
		return;
	}
	if(true_angle[0] >= 0 && true_angle[0] < 180){
		MOTOR1.direction = CCW;
		MOTOR1.rotate_degree = true_angle[0];
		PTO_config(&MOTOR1);
		PTO_run(&MOTOR1);
	}
	else{
		MOTOR1.direction = CW;
		MOTOR1.rotate_degree = 360 - true_angle[0];
		PTO_config(&MOTOR1);
		PTO_run(&MOTOR1);
	}

	if(true_angle[1] >= 0 && true_angle[1] < 180){
		MOTOR2.direction = CW;
		MOTOR2.rotate_degree = true_angle[1];
		PTO_config(&MOTOR2);
		PTO_run(&MOTOR2);
	}
	else{
		MOTOR2.direction = CCW;
		MOTOR2.rotate_degree = 360 - true_angle[1];
		PTO_config(&MOTOR2);
		PTO_run(&MOTOR2);
	}

	if(true_angle[2] >= 0 && true_angle[2] < 180){
		MOTOR3.direction = CW;
		MOTOR3.rotate_degree = true_angle[2];
		PTO_config(&MOTOR3);
		PTO_run(&MOTOR3);
	}
	else{
		MOTOR3.direction = CCW;
		MOTOR3.rotate_degree = 360 - true_angle[2];
		PTO_config(&MOTOR3);
		PTO_run(&MOTOR3);
	}
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0);
}

void init_pio_1_input_interrupt(){
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0);
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE, 0x1);
    alt_ic_isr_register(
    	PIO_1_IRQ_INTERRUPT_CONTROLLER_ID,
		PIO_1_IRQ,
        pio_input_1_isr,
        NULL,
        NULL
    );
}



