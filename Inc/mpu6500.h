/*
 * mpu6500.h
 *
 *  Created on: 26.09.2019
 *      Author: Konto_U¿ytkowe
 */

#ifndef MPU6500_H_
#define MPU6500_H_

#include  <stdint.h>
#include "usart.h"
#include <string.h>
#include "ROV_Tasks.h"

uint8_t  read_byte ( uint8_t reg);

void  write_byte ( uint8_t reg, uint8_t val);

void  mpu6500_init ( void );

float  mpu6500_read_gyro_z ( void );

float mpu6500_read_acce_x( void );
float mpu6500_read_acce_y( void );
float mpu6500_read_acce_z( void );

void usart3_print(char * msg);


#endif /* MPU6500_H_ */
