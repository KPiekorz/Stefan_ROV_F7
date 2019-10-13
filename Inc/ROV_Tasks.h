/*
 * ROV_Tasks.h
 *
 *  Created on: 08.10.2019
 *      Author: Konto_U¿ytkowe
 */

#ifndef ROV_TASKS_H_
#define ROV_TASKS_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "main.h"
#include "cmsis_os.h"
#include "mpu6500.h"
#include "math.h"


/* Task functions prototypes */
TaskHandle_t xTaskThrusterHorizontalHandle;
TaskHandle_t xTaskThrusterVerticalHandle;
TaskHandle_t xTaskAccelerometerHandle;


/* Task handlers */
void vTaskThrusterHorizontal(void *p);
void vTaskThrusterVertical(void *p);
void vTaskAccelerometer(void *p);


/* variables */
char usr_msg[100];
SemaphoreHandle_t xMutexSendMsg;

/* functions prototypes */
void uart3_send(char *msg);
int adc_to_pwm(uint16_t  adc_value);
void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);
void ftos_negative_numbers(float n, char *res, int afterpoint);
char* concat(const char *s1, const char *s2);




#endif /* ROV_TASKS_H_ */
