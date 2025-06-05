/*
 * uart.c
 *
 *  Created on: Apr 20, 2025
 *      Author: Admin
 */
#include "uart.h"

static alt_u8 *data_rx;
static alt_u32 count = 0;

alt_u8 end_of_command;

MOTOR_t MOTOR1;
MOTOR_t MOTOR2;
MOTOR_t MOTOR3;

static parse_cmd state = Idle;

alt_u8 check_valid_angle(){
	alt_u8 status = TRUE;
	int temp;
	if(MOTOR2.direction == CCW){
		temp = MOTOR2.rotate_degree/4 + motor_angle[1];
		if((temp % 360) > LOWER_BOUND_MOTOR2 && (temp % 360) < UPPER_BOUND_MOTOR2){
			status = FALSE;
			return status;
		}
		temp = MOTOR2.rotate_degree/2 + motor_angle[1];
		if((temp % 360) > LOWER_BOUND_MOTOR2 && (temp % 360) < UPPER_BOUND_MOTOR2){
			status = FALSE;
			return status;
		}
		temp = MOTOR2.rotate_degree + motor_angle[1];
		if((temp % 360) > LOWER_BOUND_MOTOR2 && (temp % 360) < UPPER_BOUND_MOTOR2){
			status = FALSE;
			return status;
		}
	}
	else{
		temp = motor_angle[1] - MOTOR2.rotate_degree/4;
		if(temp < 0){
			temp += 360;
		}
		if(temp > LOWER_BOUND_MOTOR2 && temp < UPPER_BOUND_MOTOR2){
			status = FALSE;
			return status;
		}
		temp = motor_angle[1] - MOTOR2.rotate_degree/2;
		if(temp < 0){
			temp += 360;
		}
		if(temp > LOWER_BOUND_MOTOR2 && temp < UPPER_BOUND_MOTOR2){
			status = FALSE;
			return status;
		}
		temp = motor_angle[1] - MOTOR2.rotate_degree;
		if(temp < 0){
			temp += 360;
		}
		if(temp > LOWER_BOUND_MOTOR2 && temp < UPPER_BOUND_MOTOR2){
			status = FALSE;
			return status;
		}
	}

	if(MOTOR3.direction == CW){
		temp = MOTOR3.rotate_degree/4 + motor_angle[2];
		if((temp % 360) > LOWER_BOUND_MOTOR3 && (temp % 360) < UPPER_BOUND_MOTOR3){
			status = FALSE;
			return status;
		}
		temp = MOTOR3.rotate_degree/2 + motor_angle[2];
		if((temp % 360) > LOWER_BOUND_MOTOR3 && (temp % 360) < UPPER_BOUND_MOTOR3){
			status = FALSE;
			return status;
		}
		temp = MOTOR3.rotate_degree + motor_angle[2];
		if((temp % 360) > LOWER_BOUND_MOTOR3 && (temp % 360) < UPPER_BOUND_MOTOR3){
			status = FALSE;
			return status;
		}
	}
	else{
		temp = motor_angle[2] - MOTOR3.rotate_degree/4;
		if(temp < 0){
			temp += 360;
		}
		if(temp > LOWER_BOUND_MOTOR3 && temp < UPPER_BOUND_MOTOR3){
			status = FALSE;
			return status;
		}
		temp = motor_angle[2] - MOTOR3.rotate_degree/2;
		if(temp < 0){
			temp += 360;
		}
		if(temp > LOWER_BOUND_MOTOR3 && temp < UPPER_BOUND_MOTOR3){
			status = FALSE;
			return status;
		}
		temp = motor_angle[2] - MOTOR3.rotate_degree;
		if(temp < 0){
			temp += 360;
		}
		if(temp > LOWER_BOUND_MOTOR3 && temp < UPPER_BOUND_MOTOR3){
			status = FALSE;
			return status;
		}
	}
	return status;
}

void uart_innit(){
	  alt_ic_isr_register(UART_0_IRQ_INTERRUPT_CONTROLLER_ID, UART_0_IRQ,(void*) uart_isr,NULL, 0);
	  IOWR_ALTERA_AVALON_UART_CONTROL(UART_0_BASE, ALTERA_AVALON_UART_CONTROL_RRDY_MSK);
}

void uart_isr(void *context, alt_u32 id){
	data_rx[count] = IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
	if(data_rx[count] == ';'){
		uart_read_cmd();
		if(check_valid_angle() == FALSE){
			return;
		}
		PTO_config(&MOTOR1);
		PTO_config(&MOTOR2);
		PTO_config(&MOTOR3);
		PTO_run(&MOTOR1);
		PTO_run(&MOTOR2);
		PTO_run(&MOTOR3);
	}
	else{
		count++;
	}
	IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
}

void uart_tx(alt_u8 *data_send, alt_u32 numb_byte){
	alt_u8 i;
	for(i = 0; i < numb_byte; i++){
		IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, data_send[i]);
		usleep(50);
	}
}

void uart_read_cmd(){
	alt_u8 end_of_motor1 = 0;
	switch(state){
		case Idle:
			state = Angle_1;
		case Angle_1:
			MOTOR1.rotate_degree = atoi((const char*)(data_rx + 2));
			state = Direction_1;
		case Direction_1:
			if(MOTOR1.rotate_degree < 10){
				if(!strncmp((const char*)(data_rx + 3), "CC", 2)){
					MOTOR1.direction = CCW;
				}
				else{
					MOTOR1.direction = CW;
				}
				end_of_motor1 = 5;
			}
			else if((MOTOR1.rotate_degree >= 10) && (MOTOR1.rotate_degree < 100)){
				if(!strncmp((const char*)(data_rx + 4), "CC", 2)){
					MOTOR1.direction = CCW;
				}
				else{
					MOTOR1.direction = CW;
				}
				end_of_motor1 = 6;
			}
			else{
				if(!strncmp((const char*)(data_rx + 5), "CC", 2)){
					MOTOR1.direction = CCW;
				}
				else{
					MOTOR1.direction = CW;
				}
				end_of_motor1 = 7;
			}
			state = Angle_2;
		case Angle_2:
			MOTOR2.rotate_degree = atoi((const char*)(data_rx + end_of_motor1 + 2));
			state = Direction_2;
		case Direction_2:
			if(MOTOR2.rotate_degree < 10){
				if(!strncmp((const char*)(data_rx + end_of_motor1 + 3), "CC", 2)){
					MOTOR2.direction = CCW;
				}
				else{
					MOTOR2.direction = CW;
				}
				end_of_motor1 += 5;
			}
			else if((MOTOR2.rotate_degree >= 10) && (MOTOR2.rotate_degree < 100)){
				if(!strncmp((const char*)(data_rx + end_of_motor1 + 4), "CC", 2)){
					MOTOR2.direction = CCW;
				}
				else{
					MOTOR2.direction = CW;
				}
				end_of_motor1 += 6;
			}
			else{
				if(!strncmp((const char*)(data_rx + end_of_motor1 + 5), "CC", 2)){
					MOTOR2.direction = CCW;
				}
				else{
					MOTOR2.direction = CW;
				}
				end_of_motor1 += 7;
			}
			state = Angle_3;
		case Angle_3:
			MOTOR3.rotate_degree = atoi((const char*)(data_rx + end_of_motor1 + 2));
			state = Direction_3;
		case Direction_3:
			if(MOTOR3.rotate_degree < 10){
				if(!strncmp((const char*)(data_rx + end_of_motor1 + 3), "CC", 2)){
					MOTOR3.direction = CCW;
				}
				else{
					MOTOR3.direction = CW;
				}
			}
			else if((MOTOR3.rotate_degree >= 10) && (MOTOR3.rotate_degree < 100)){
				if(!strncmp((const char*)(data_rx + end_of_motor1 + 4), "CC", 2)){
					MOTOR3.direction = CCW;
				}
				else{
					MOTOR3.direction = CW;
				}
			}
			else{
				if(!strncmp((const char*)(data_rx + end_of_motor1 + 5), "CC", 2)){
					MOTOR3.direction = CCW;
				}
				else{
					MOTOR3.direction = CW;
				}
			}
			state = End;
		case End:
			state = Idle;
	}
	memset(data_rx, 0, count + 5);
	count = 0;
}
