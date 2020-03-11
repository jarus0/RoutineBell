/*
 * RMTClass.h
 *
 *  Created on: 29-Jan-2020
 *      Author: suraj
 */

#ifndef MAIN_RMTCLASS_H_
#define MAIN_RMTCLASS_H_


#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <soc/rmt_struct.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <stdio.h>


#define WS2812_PIN	5

#define delay_ms(ms) vTaskDelay((ms) / portTICK_RATE_MS)



/* Created 19 Nov 2016 by Chris Osborn <fozztexx@fozztexx.com>
 * http://insentricity.com
 *
 * Uses the RMT peripheral on the ESP32 for very accurate timing of
 * signals sent to the WS2812 LEDs.
 *
 * This code is placed in the public domain (or CC0 licensed, at your option).
 */

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <soc/rmt_struct.h>
#include <soc/dport_reg.h>
#include <driver/gpio.h>
#include <soc/gpio_sig_map.h>
#include <esp_intr.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <driver/rmt.h>

#define ETS_RMT_CTRL_INUM	18
#define ESP_RMT_CTRL_DISABLE	ESP_RMT_CTRL_DIABLE /* Typo in esp_intr.h */

#define DIVIDER		4 /* Above 4, timings start to deviate*/
#define DURATION	12.5 /* minimum time of a single RMT duration
				in nanoseconds based on clock */

#define PULSE_T0H	(  350 / (DURATION * DIVIDER));
#define PULSE_T1H	(  900 / (DURATION * DIVIDER));
#define PULSE_T0L	(  900 / (DURATION * DIVIDER));
#define PULSE_T1L	(  350 / (DURATION * DIVIDER));
#define PULSE_TRS	(50000 / (DURATION * DIVIDER));

#define MAX_PULSES	32

#define RMTCHANNEL	0
#include <stdint.h>

typedef union {
  struct __attribute__ ((packed)) {
    uint8_t r, g, b;
  };
  uint32_t num;
} rgbVal;
extern void ws2812_init(int gpioNum);
extern void ws2812_setColors(unsigned int length, rgbVal *array);

inline rgbVal makeRGBVal(uint8_t r, uint8_t g, uint8_t b)
{
  rgbVal v;


  v.r = r;
  v.g = g;
  v.b = b;
  return v;
}
typedef union {
  struct {
    uint32_t duration0:15;
    uint32_t level0:1;
    uint32_t duration1:15;
    uint32_t level1:1;
  };
  uint32_t val;
} rmtPulsePair;

	static uint8_t *ws2812_buffer = NULL;
	static unsigned int ws2812_pos, ws2812_len, ws2812_half;
	static xSemaphoreHandle ws2812_sem = NULL;
	static intr_handle_t rmt_intr_handle = NULL;
	static rmtPulsePair ws2812_bits[2];



class RMTClass {
public:
	RMTClass();
	virtual ~RMTClass();

	bool jRainbowFlag = false;


	int _intensity = 255;		// 0 to 255

	const uint8_t anim_step = 10;
	const uint8_t anim_max = 250;
	const uint8_t pixel_count = 2; // Number of your "pixels"
	const uint8_t delay = 25; // duration between color changes
	rgbVal color = makeRGBVal(anim_max, 0, 0);
	uint8_t step = 0;
	rgbVal color2 = makeRGBVal(anim_max, 0, 0);
	uint8_t step2 = 0;
	rgbVal *pixels;
	//rgbVal pixels[1];

	void setIntensity(int tempIntesity);
	//int _intensity;
	//void SetIntensity();
	void jRainbowStart(bool flag);

	void rmtService();
	static void myInit();
	//void rainbow(void *pvParameters);



	static void ws2812_initRMTChannel(int);
	static void ws2812_copy();
	static void ws2812_handleInterrupt(void*);
	//void ws2812_setColors(unsigned int length, rgbVal *array, int intensity);
	void ws2812_setColors(unsigned int length, rgbVal *array, int intensity = 100);
	//static void ws2812_setColors(unsigned int, rgbVal*);


	void ws2812_init(int);
};

#endif /* MAIN_RMTCLASS_H_ */
