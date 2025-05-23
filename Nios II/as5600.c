/*
 * as5600.c
 *
 *  Created on: May 22, 2025
 *      Author: Admin
 */
#include "as5600.h"
#include "main.h"


static alt_u8 reg_address = 0x0B;
static alt_u8 reg_raw_angle_8b = 0x0D;
static alt_u8 reg_raw_angle_4b = 0x0C;

static alt_u8 reg_value;
static alt_u8 raw_angle_8b;
static alt_u8 raw_angle_4b;

ALT_AVALON_I2C_DEV_t *i2c_dev;  //pointer to instance structure
ALT_AVALON_I2C_STATUS_CODE status;

alt_u32 raw_angle;

void as5600_innit(){
	i2c_dev = alt_avalon_i2c_open("/dev/i2c_0");
	if (NULL==i2c_dev)
	{
		alt_putstr("Error: Cannot find /dev/i2c_0\n");
	    return;
	}
	else{
		alt_putstr("Connect successfully to as5600\n");
	}
	alt_avalon_i2c_master_target_set(i2c_dev, DEV_ADDR);
}

void as5600_read_angle(){
	alt_avalon_i2c_master_tx_rx(i2c_dev, &reg_raw_angle_8b, 1, &raw_angle_8b, 1, 0);
	alt_avalon_i2c_master_tx_rx(i2c_dev, &reg_raw_angle_4b, 1, &raw_angle_4b, 1, 0);
	raw_angle = ((alt_u32)raw_angle_8b | (alt_u32)(raw_angle_4b << 8)) * 360 / 4096;
	printf("Raw angle = %d\n", (int)raw_angle);
}

