/*
 * main.h
 *
 *  Created on: Apr 21, 2025
 *      Author: Admin
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "sys/alt_stdio.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "alt_types.h"

#define pulse_per_degree  	347

#define CCW				  	0
#define CW					1

#define FALSE				0
#define	TRUE				1

#define MOTOR_0				0
#define MOTOR_1				1
#define MOTOR_2				2

#define start_degree		6

#define LOWER_BOUND_MOTOR2	100
#define UPPER_BOUND_MOTOR2	290

#define LOWER_BOUND_MOTOR3	150
#define UPPER_BOUND_MOTOR3	270

typedef struct{
	alt_u8 direction;
	alt_u8 motor_ID;
	alt_u16 rotate_degree;
}MOTOR_t;

typedef enum{
	Idle,
	Angle_1,
	Direction_1,
	Angle_2,
	Direction_2,
	Angle_3,
	Direction_3,
	End
}parse_cmd;


extern int motor_angle[3];
extern int true_angle[3];



#endif /* MAIN_H_ */
