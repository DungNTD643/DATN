/*
 * uart.c
 *
 *  Created on: Apr 20, 2025
 *      Author: Admin
 */
#include "uart.h"

static alt_u8 *data_rx;
static alt_u32 count = 0;
static alt_u8 end_of_command;

MOTOR_t MOTOR1;
MOTOR_t MOTOR2;

static parse_cmd state = Idle;
void uart_innit(){
	  alt_ic_isr_register(UART_0_IRQ_INTERRUPT_CONTROLLER_ID, UART_0_IRQ,(void*) uart_isr,NULL, 0);
	  IOWR_ALTERA_AVALON_UART_CONTROL(UART_0_BASE, ALTERA_AVALON_UART_CONTROL_RRDY_MSK);
}

void uart_isr(void *context, alt_u32 id){
	data_rx[count] = IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
	if(data_rx[count] == ';'){
		end_of_command = 1;
	}
	count++;
	IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
}

void uart_tx(alt_u8 *data_send, alt_u32 numb_byte){
	alt_u8 i;
	for(i = 0; i < numb_byte; i++){
		IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, data_send[i]);
		usleep(50);
	}
}

alt_u8 uart_cmd_receive(){
	if(end_of_command == 1){
		end_of_command = 0;
		return 1;
	}
	return 0;
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
			}
			else if((MOTOR2.rotate_degree >= 10) && (MOTOR2.rotate_degree < 100)){
				if(!strncmp((const char*)(data_rx + end_of_motor1 + 4), "CC", 2)){
					MOTOR2.direction = CCW;
				}
				else{
					MOTOR2.direction = CW;
				}
			}
			else{
				if(!strncmp((const char*)(data_rx + end_of_motor1 + 5), "CC", 2)){
					MOTOR2.direction = CCW;
				}
				else{
					MOTOR2.direction = CW;
				}
			}
			state = End;
		case End:
			state = Idle;
	}
	memset(data_rx, 0, count);
	count = 0;
}
