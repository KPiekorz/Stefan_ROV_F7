/*
 * mpu6500.c
 *
 *  Created on: 26.09.2019
 *      Author: Konto_U¿ytkowe
 */


#include "mpu6500.h"

#include "main.h"

#include "spi.h"

// Register map
#define WHO_AM_I 					0x75		// this register is used to verify the identity of the device - 8-bit device ID

#define PWR_MGMT_1 					0x6B		// power management 1
#define PWR_MGMT_2					0x6C		// power menagement 2

#define MPU6500_RA_CONFIG 			0x1A

// gyro
#define GYRO_CONFIG 				0x1B
#define GYRO_FACTOR					(16.4)		//(32678.0/2.0)
#define GYRO_ZOUT_H					0x47
#define GYRO_ZOUT_L					0x48

// acce
#define ACCE_CONFIG					0x1C
#define ACCE_XOUT_H				0x3B
#define ACCE_XOUT_L				0x3C
#define ACCE_YOUT_H				0x3D
#define ACCE_YOUT_L				0x3E
#define ACCE_ZOUT_H				0x3F
#define ACCE_ZOUT_L				0x40


/*
 @brief spi : read 1 byte
 @param uint8_t Register
 @return read 1byte data
*/
uint8_t read_byte( uint8_t reg )
{
  uint8_t ret,val;
  HAL_GPIO_WritePin( gyro_cs_GPIO_Port, gyro_cs_Pin, GPIO_PIN_RESET ); //cs = Low;
  ret = reg | 0x80;  // MSB = 1
  HAL_SPI_Transmit( &hspi1, &ret,1,100 ); // sent 1byte(address)
  HAL_SPI_Receive( &hspi1,&val,1,100 ); // read 1byte(read data)
  HAL_GPIO_WritePin( gyro_cs_GPIO_Port,gyro_cs_Pin, GPIO_PIN_SET );  //cs = High;
  return val;
}

/*
 @brief spi : write 1 byte
 @param uint8_t Register
 @param uint8_t Write Data
*/
void write_byte( uint8_t reg, uint8_t val )
{
  uint8_t ret;
  ret = reg & 0x7F ; // MSB = 0
  HAL_GPIO_WritePin( gyro_cs_GPIO_Port, gyro_cs_Pin, GPIO_PIN_RESET ); // cs = Low;
  HAL_SPI_Transmit( &hspi1, &ret,1,100 ); // sent 1byte(address)
  HAL_SPI_Transmit( &hspi1, &val,1,100 ); // read 1byte(write data)
  HAL_GPIO_WritePin( gyro_cs_GPIO_Port,gyro_cs_Pin, GPIO_PIN_SET ); // cs = High;
}

/*
 * @breif initialize mpu 6500
*/

void mpu6500_init( void )
{
  uint8_t who_am_i;

  HAL_Delay( 100 ); // wait start up
  who_am_i = read_byte( WHO_AM_I ); // 1. read who am i
  sprintf(usr_msg, "0x%x\r\n", who_am_i ); // 2. check who am i value
  uart3_send(usr_msg);

  // 2. error check
  if ( who_am_i != 0x73 ){
    while(1){
      sprintf(usr_msg, "gyro_error\r\n");
      uart3_send(usr_msg);
    }
  }

  HAL_Delay( 50 ); // wait

  write_byte( PWR_MGMT_1, 0x00 ); // 3. set pwr_might

  HAL_Delay( 50 );

  write_byte( MPU6500_RA_CONFIG, 0x00 ); // 4. set config

  HAL_Delay( 50 );

  write_byte( GYRO_CONFIG, 0x18 ); // 5. set gyro config

  HAL_Delay( 50 );

}

/*
 * @breif read z axis
 * @return float gyro_z deg/sec
*/
float mpu6500_read_gyro_z( void )
{
  int16_t gyro_z;
  float omega;

  // H:8bit shift, Link h and l
  gyro_z = (int16_t)( (int16_t)(read_byte(GYRO_ZOUT_H) << 8 ) | read_byte(GYRO_ZOUT_L) );

  omega = (float)( gyro_z / GYRO_FACTOR ); // dps to deg/sec

  return omega;
}

/*
 * @breif mpu6500_read_acce_x
 * @return
*/
float mpu6500_read_acce_x( void )
{
  int16_t acce_x;

  // H:8bit shift, Link h and l
  acce_x = (int16_t)( (int16_t)(read_byte(ACCE_XOUT_H) << 8 ) | read_byte(ACCE_XOUT_L) );

  return acce_x;
}

/*
 * @breif mpu6500_read_acce_y
 * @return
*/
float mpu6500_read_acce_y( void )
{
  int16_t acce_y;

  // H:8bit shift, Link h and l
  acce_y = (int16_t)( (int16_t)(read_byte(ACCE_YOUT_H) << 8 ) | read_byte(ACCE_YOUT_L) );

  return acce_y;
}

/*
 * @breif mpu6500_read_acce_x
 * @return
*/
float mpu6500_read_acce_z( void )
{
  int16_t acce_z;

  // H:8bit shift, Link h and l
  acce_z = (int16_t)( (int16_t)(read_byte(ACCE_ZOUT_H) << 8 ) | read_byte(ACCE_ZOUT_L) );

  return acce_z;
}



void usart3_print(char * msg){
	HAL_UART_Transmit(&huart3, (uint8_t*) msg, strlen(msg), HAL_MAX_DELAY);
}

