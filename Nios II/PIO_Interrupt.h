/*
 * PIO_Interrupt.h
 *
 *  Created on: Jun 4, 2025
 *      Author: Admin
 */

#ifndef PIO_INTERRUPT_H_
#define PIO_INTERRUPT_H_

#include "sys/alt_stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include "alt_types.h"
#include "main.h"
#include "uart.h"

void pio_input_0_isr(void* context, alt_u32 id);
void init_pio_0_input_interrupt();
void pio_input_1_isr(void* context, alt_u32 id);
void init_pio_1_input_interrupt();

extern int off_set[3];

#endif /* PIO_INTERRUPT_H_ */
