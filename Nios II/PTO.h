/*
 * PTO.h
 *
 *  Created on: Apr 19, 2025
 *      Author: Admin
 */

#ifndef PTO_H_
#define PTO_H_

#include "sys/alt_stdio.h"
#include "io.h"
#include "system.h"
#include "unistd.h"
#include "stdio.h"
#include "alt_types.h"
#include "main.h"

void PTO_config(MOTOR_t *user_config);
void PTO_angle(MOTOR_t *user_config);
void PTO_speed();
void PTO_innit();


#endif /* PTO_H_ */
