/*
 * CommunicationMode.h
 *
 *  Created on: 06-Jan-2020
 *      Author: suraj
 */

#ifndef MAIN_HARDWARE_CONNECTION_MODE_COMMUNICATIONMODE_H_
#define MAIN_HARDWARE_CONNECTION_MODE_COMMUNICATIONMODE_H_

//*
#define sta_EXAMPLE_ESP_WIFI_SSID      "Sam"
#define sta_EXAMPLE_ESP_WIFI_PASS      "chandasingh"
#define sta_EXAMPLE_ESP_MAXIMUM_RETRY  15 // jarus:futurethink

#define ap_EXAMPLE_ESP_WIFI_SSID      "esp32ApMode"
#define ap_EXAMPLE_ESP_WIFI_PASS      "mypassword123"
#define ap_EXAMPLE_MAX_STA_CONN       10
//*/

#include "mdns.h"
#include <Arduino.h>

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include <stdio.h>
#include <iostream>
#include <cstring>

#include <esp_http_server.h>
#include "WebserverHandler.h"
#include "jglobal.h"

//const char *TAG = "wifi ap+sta";
static int s_retry_num = 0;
const int WIFI_CONNECTED_BIT = BIT0; /* The event group allows multiple bits for each event, but we only care about one event are we connected to the AP with an IP? */
const int WIFI_CONNECTED_BIT1 = BIT1;
static EventGroupHandle_t s_wifi_event_group;


class CommunicationMode {
public:
	CommunicationMode();
	virtual ~CommunicationMode();

	httpd_handle_t *_jserver;
	static WebserverHandler obj_webSer;

	static esp_err_t event_handler(void *ctx, system_event_t *event);

	void jwifi_init_softap_sta_both(void *arg);
	void jwifi_init_AP(void *arg);
	void jwifi_init_STA(void *arg);


// future task : multiple router info can save
//	std::string sta_ssid = "Avinashi";
//	std::string sta_pass = "Avinashi#IoTick";
//	jStr sta_ssid = "myssid";
//	jStr sta_pass = "mypassword";

//	std::string sta_ssid = "hello";
//	std::string sta_pass = "kiwihope";
	std::string sta_ssid = "Sam";
	std::string sta_pass = "chandasingh";

//	std::string sta_ssid = "myssid";
//	std::string sta_pass = "mypassword";

	jStr apa_ssid = "SmartRemote@" + objJarusAccessories.sstr_chipID;
	jStr apa_pass = "smartremote";

	jStr mdnsName = "mdnsName";
	jStr mdnsInstane = "mdnsInstane";
	jStr mdnsSomethingunk = "mdnsInstaneJa";

/*	std::string jssid = "some ssidasas";
	std::string jpass = "some paswoed2322";

	std::string jssid1 = "myssid";
	std::string jpass2 = "mypassword";
*/


};

#endif /* MAIN_HARDWARE_CONNECTION_MODE_COMMUNICATIONMODE_H_ */
