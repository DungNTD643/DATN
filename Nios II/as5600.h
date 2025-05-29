/*
 * as5600.h
 *
 *  Created on: May 22, 2025
 *      Author: Admin
 */

#ifndef AS5600_H_
#define AS5600_H_
#include "altera_avalon_i2c.h"

#define DEV_ADDR	0x36

void as5600_innit();
alt_u32 as5600_read_angle(ALT_AVALON_I2C_DEV_t *i2c_dev);

extern ALT_AVALON_I2C_DEV_t *i2c_dev[3];


#endif /* AS5600_H_ */
