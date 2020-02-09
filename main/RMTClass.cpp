/*
 * RMTClass.cpp
 *
 *  Created on: 29-Jan-2020
 *      Author: suraj
 */

#include "RMTClass.h"

RMTClass::RMTClass() {
	// TODO Auto-generated constructor stub
	pixels =(rgbVal*) malloc(sizeof(rgbVal) * pixel_count);
}

RMTClass::~RMTClass() {
	// TODO Auto-generated destructor stub
}


void RMTClass::jRainbowStart(bool flag)
{
	jRainbowFlag = flag;
}

void RMTClass::setIntensity(int tempIntesity)
{
	_intensity = tempIntesity;
}
void RMTClass::rmtService()
{
	if (jRainbowFlag)
	{

			color = color2;
			step = step2;

			for (uint8_t i = 0; i < pixel_count; i++) {
			pixels[i] = color;

			if (i == 1) {
			color2 = color;
			step2 = step;
			}

			switch (step) {
				case 0:
				color.g += anim_step;
				if (color.g >= anim_max)
				  step++;
				break;
				case 1:
				color.r -= anim_step;
				if (color.r == 0)
				  step++;
				break;
				case 2:
				color.b += anim_step;
				if (color.b >= anim_max)
				  step++;
				break;
				case 3:
				color.g -= anim_step;
				if (color.g == 0)
				  step++;
				break;
				case 4:
				color.r += anim_step;
				if (color.r >= anim_max)
				  step++;
				break;
				case 5:
				color.b -= anim_step;
				if (color.b == 0)
				  step = 0;
				break;
			}
		}

		ws2812_setColors(pixel_count, pixels, _intensity);

		delay_ms(delay);
	}
}


void RMTClass::ws2812_initRMTChannel(int rmtChannel)
{
  RMT.apb_conf.fifo_mask = 1;  //enable memory access, instead of FIFO mode.
  RMT.apb_conf.mem_tx_wrap_en = 1; //wrap around when hitting end of buffer
  RMT.conf_ch[rmtChannel].conf0.div_cnt = DIVIDER;
  RMT.conf_ch[rmtChannel].conf0.mem_size = 1;
  RMT.conf_ch[rmtChannel].conf0.carrier_en = 0;
  RMT.conf_ch[rmtChannel].conf0.carrier_out_lv = 1;
  RMT.conf_ch[rmtChannel].conf0.mem_pd = 0;

  RMT.conf_ch[rmtChannel].conf1.rx_en = 0;
  RMT.conf_ch[rmtChannel].conf1.mem_owner = 0;
  RMT.conf_ch[rmtChannel].conf1.tx_conti_mode = 0;    //loop back mode.
  RMT.conf_ch[rmtChannel].conf1.ref_always_on = 1;    // use apb clock: 80M
  RMT.conf_ch[rmtChannel].conf1.idle_out_en = 1;
  RMT.conf_ch[rmtChannel].conf1.idle_out_lv = 0;

  return;
}

void RMTClass::ws2812_copy()
{
  unsigned int i, j, offset, len, bit;


  offset = ws2812_half * MAX_PULSES;
  ws2812_half = !ws2812_half;

  len = ws2812_len - ws2812_pos;
  if (len > (MAX_PULSES / 8))
    len = (MAX_PULSES / 8);

  if (!len) {
    for (i = 0; i < MAX_PULSES; i++)
      RMTMEM.chan[RMTCHANNEL].data32[i + offset].val = 0;
    return;
  }

  for (i = 0; i < len; i++) {
    bit = ws2812_buffer[i + ws2812_pos];
    for (j = 0; j < 8; j++, bit <<= 1) {
      RMTMEM.chan[RMTCHANNEL].data32[j + i * 8 + offset].val =
	ws2812_bits[(bit >> 7) & 0x01].val;
    }
    if (i + ws2812_pos == ws2812_len - 1)
      RMTMEM.chan[RMTCHANNEL].data32[7 + i * 8 + offset].duration1 = PULSE_TRS;
  }

  for (i *= 8; i < MAX_PULSES; i++)
    RMTMEM.chan[RMTCHANNEL].data32[i + offset].val = 0;

  ws2812_pos += len;
  return;
}

void RMTClass::ws2812_handleInterrupt(void *arg)
{
  portBASE_TYPE taskAwoken = 0;


  if (RMT.int_st.ch0_tx_thr_event) {
    ws2812_copy();
    RMT.int_clr.ch0_tx_thr_event = 1;
  }
  else if (RMT.int_st.ch0_tx_end && ws2812_sem) {
    xSemaphoreGiveFromISR(ws2812_sem, &taskAwoken);
    RMT.int_clr.ch0_tx_end = 1;
  }

  return;
}

void RMTClass::ws2812_init(int gpioNum)
{
  DPORT_SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_RMT_CLK_EN);
  DPORT_CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_RMT_RST);

  rmt_set_pin((rmt_channel_t)RMTCHANNEL, RMT_MODE_TX, (gpio_num_t)gpioNum);

  ws2812_initRMTChannel(RMTCHANNEL);

  RMT.tx_lim_ch[RMTCHANNEL].limit = MAX_PULSES;
  RMT.int_ena.ch0_tx_thr_event = 1;
  RMT.int_ena.ch0_tx_end = 1;

  ws2812_bits[0].level0 = 1;
  ws2812_bits[0].level1 = 0;
  ws2812_bits[0].duration0 = PULSE_T0H;
  ws2812_bits[0].duration1 = PULSE_T0L;
  ws2812_bits[1].level0 = 1;
  ws2812_bits[1].level1 = 0;
  ws2812_bits[1].duration0 = PULSE_T1H;
  ws2812_bits[1].duration1 = PULSE_T1L;

  esp_intr_alloc(ETS_RMT_INTR_SOURCE, 0, ws2812_handleInterrupt, NULL, &rmt_intr_handle);

  return;
}


//void RMTClass::SetIntensity()
//{
//
//	rgbVal tempColor;
//
//	JJLOG.println ("white color");
//	tempColor = {255,255,255}; objRGB.ws2812_setColors(2, &tempColor);delay(1000);
//	delay(2000);
//
//	JJLOG.println ("ok reduxing brithness");
//	int colorRGB[3];
//
//	colorRGB[0] = tempColor.r;
//	colorRGB[1] = tempColor.g;
//	colorRGB[2] = tempColor.b;
//
//	rgbVal newColor;
//
//	for (int intensity = 100; intensity > 0 ; intensity--)
//	{
//
//		newColor.r = tempColor.r *  intensity / 100;
//		newColor.g = tempColor.g *  intensity / 100;
//		newColor.b = tempColor.b *  intensity / 100;
//		objRGB.ws2812_setColors(2, &newColor);
//		delay(100);
//	}
//
//
//}


void RMTClass::ws2812_setColors(unsigned int length, rgbVal *array, int intensity)
{

	// this is called patiya
	array->r = array->r * intensity / 255;
	array->g = array->g * intensity / 255;
	array->b = array->b * intensity / 255;
//
//	Serial.println ("after conversion");
//	Serial.println(array->r);
//	Serial.println(array->g);
//	Serial.println(array->b);


	unsigned int i;

  ws2812_len = (length * 3) * sizeof(uint8_t);
  ws2812_buffer = (uint8_t*) malloc(ws2812_len);

  for (i = 0; i < length; i++) {
    ws2812_buffer[0 + i * 3] = array[i].g;
    ws2812_buffer[1 + i * 3] = array[i].r;
    ws2812_buffer[2 + i * 3] = array[i].b;
  }

  ws2812_pos = 0;
  ws2812_half = 0;

  ws2812_copy();

  if (ws2812_pos < ws2812_len)
    ws2812_copy();

  ws2812_sem = xSemaphoreCreateBinary();

  RMT.conf_ch[RMTCHANNEL].conf1.mem_rd_rst = 1;
  RMT.conf_ch[RMTCHANNEL].conf1.tx_start = 1;

  xSemaphoreTake(ws2812_sem, portMAX_DELAY);
  vSemaphoreDelete(ws2812_sem);
  ws2812_sem = NULL;

  free(ws2812_buffer);

  return;
}


