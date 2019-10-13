/*
 * ROV_Tasks.c
 *
 *  Created on: 08.10.2019
 *      Author: Konto_U¿ytkowe
 */


#include "ROV_Tasks.h"


extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim1;
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart3;



/*
 *
 */
void vTaskThrusterHorizontal(void *p){

	uint16_t duty_pwm1 = 0, duty_pwm2 = 0;
	uint32_t joystick[2];

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // PC6
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); // PC7

	TIM3->CCR1 = 1000;
	TIM3->CCR2 = 1000;

	HAL_ADC_Start_DMA(&hadc1, joystick, 2);

	vTaskDelay(1000);

	while(1){

//		sprintf(usr_msg, "X: %d, Y: %d\r\n", adc_to_pwm(joystick[0]), adc_to_pwm(joystick[1]));
//		uart3_send(usr_msg);

		duty_pwm1 = adc_to_pwm(joystick[0]);
		duty_pwm2 = adc_to_pwm(joystick[1]);

		TIM3->CCR1 = duty_pwm1;
		TIM3->CCR2 = duty_pwm2;

		vTaskDelay(100);

	}

}

void vTaskThrusterVertical(void * p){

	uint16_t pulse_count;
	uint16_t position;
	uint16_t duty_pwm3 = 0;

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3); // PC8
	TIM3->CCR3 = 5000;
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);

	while(1){

		pulse_count = TIM1->CNT;
		position =  pulse_count/4;

//		sprintf(usr_msg, "pulse_count: %d, position: %d\r\n", pulse_count, position);
//		uart3_send(usr_msg);

		vTaskDelay(100);

	}

}


void vTaskAccelerometer(void *p){

	int16_t a_x, a_y, a_z;
	float x, y, z;
	char s_x[20] = "";
	char s_y[20] = "";
	char s_z[20] = "";

	HAL_GPIO_WritePin( gyro_cs_GPIO_Port,gyro_cs_Pin, GPIO_PIN_SET ); // cs = High;
	mpu6500_init();

	while(1){

		if (xSemaphoreTake(xMutexSendMsg, portMAX_DELAY) == 1) {

			a_x = mpu6500_read_acce_x();
			a_y = mpu6500_read_acce_y();
			a_z = mpu6500_read_acce_z();

			x = a_x * 2.0f / 32678.0f;
			y = a_y * 2.0f / 32678.0f;
			z = a_z * 2.0f / 32678.0f;

			ftos_negative_numbers(x, s_x, 3);
			ftos_negative_numbers(y, s_y, 3);
			ftos_negative_numbers(z, s_z, 3);

			sprintf(usr_msg, "X = %s   Y = %s   Z = %s\r\n", s_x, s_y, s_z);
			uart3_send(usr_msg);

			xSemaphoreGive(xMutexSendMsg);
		}

		vTaskDelay(1000);

	}

}



/*****************************************************************************************************/

int adc_to_pwm(uint16_t  adc_value){
	return 750 + ((((float)adc_value-2048)/2048)*250);
}

void uart3_send(char *msg){
	HAL_UART_Transmit(&huart3, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);
}

// reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

void ftos_negative_numbers(float n, char *res, int afterpoint){

	if( n < 0){

		n *= (-1.0);
		ftoa(n, res, afterpoint);
		if (n < 1){
			strcpy(res, concat("-0", res));
		}else{
			strcpy(res, concat("-", res));
		}

	}else{
		ftoa(n, res, afterpoint);
		if (n < 1){
			strcpy(res, concat("0", res));
		}
	}

}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


