/*
 * app.c
 *
 *  Created on: Nov 25, 2024
 *      Author: blueb
 */

#include "app.h"
#include "math.h"
#include "hsv2rgb.h"

extern TIM_HandleTypeDef htim1;

struct hsv_colour hsv_c;
struct rgb_colour rgb_c;

void setRGB(uint16_t r, uint16_t g, uint16_t b){
	htim1.Instance->CCR1 = r;
	htim1.Instance->CCR2 = g;
	htim1.Instance->CCR3 = b;
}

void setHardRGB(){
#if 0
	/* 아래와 같이 구현이 RGB는 부드럽지 않게 깜빡이게 된다 */
	htim1.Instance->CCR1 = 50; //RED
	htim1.Instance->CCR2 = 0; //GREEN
	htim1.Instance->CCR3 = 0; //BLUE
	HAL_Delay(100);
//		htim1.Instance->ARR = 65535;
	htim1.Instance->CCR1 = 0; //RED
	htim1.Instance->CCR2 = 50; //GREEN
	htim1.Instance->CCR3 = 0; //BLUE
	HAL_Delay(100);

	htim1.Instance->CCR1 = 0; //RED
	htim1.Instance->CCR2 = 0; //GREEN
	htim1.Instance->CCR3 = 50; //BLUE
#else
	//or
	/* 아래와 같이 구현이 RGB는 부드럽지 않게 깜빡이게 된다 */
	HAL_Delay(100);
	setRGB(499, 0, 0);
	HAL_Delay(100);
	setRGB(0, 499, 0);
	HAL_Delay(100);
	setRGB(0, 0, 499);
	HAL_Delay(100);
#endif
}

void setSoftRadianRGB(){
	float valueR;
	float valueG;
	float valueB;
	static uint16_t angleR = 0;
	static uint16_t angleG = 120;
	static uint16_t angleB = 240;
	angleR++;
	angleG++;
	angleB++;
	angleR%=360;
	angleG%=360;
	angleB%=360;

	// degree to radian
	valueR = sin(angleR * M_PI / 180) * 499 + 499;
	valueG = sin(angleG * M_PI / 180) * 499 + 499;
	valueB = sin(angleB * M_PI / 180) * 499 + 499;

	setRGB((uint16_t)valueR, (uint16_t)valueG, (uint16_t)valueB);
	HAL_Delay(10);
}

void setHSV(){
	hsv_c.h = 0;
	hsv_c.s = 1;
	hsv_c.v = 1;
}

void setHsvRGB(){
	hsv2rgb(&hsv_c, &rgb_c);
	setRGB(rgb_c.r*30, rgb_c.g * 30, rgb_c.b * 30);
	hsv_c.h+=0.001;
	if(hsv_c.h >= 1.0) hsv_c.h = 0;

	HAL_Delay(5);
}

void app(){
	//PWM 타이머 시작 (핸들, 채널)
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

	//3]
	setHSV();
	///


	while(1) {
		//1]
//		setHardRGB();

		//2]
//		setSoftRadianRGB();

		//3]
		setHsvRGB();

	}
}
