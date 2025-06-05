/*
 * uart.h
 *
 *  Created on: Apr 20, 2025
 *      Author: Admin
 */

#ifndef UART_H_
#define UART_H_
#include "system.h"
#include "sys/alt_stdio.h"
#include "alt_types.h"
#include "sys/alt_irq.h"
#include "altera_avalon_uart_regs.h"
#include "string.h"
#include "main.h"
#include "PTO.h"


void uart_innit();
void uart_isr(void *context, alt_u32 id);
void uart_tx(alt_u8 *data_send, alt_u32 numb_byte);
void uart_read_cmd();
void uart_cmd_receive();

extern MOTOR_t MOTOR1;
extern MOTOR_t MOTOR2;
extern MOTOR_t MOTOR3;

extern alt_u8 end_of_command;
#endif /* UART_H_ */
