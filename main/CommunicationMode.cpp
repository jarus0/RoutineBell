/*
 * CommunicationMode.cpp
 *
 *  Created on: 06-Jan-2020
 *      Author: suraj
 */


#include "CommunicationMode.h"

CommunicationMode::CommunicationMode() {
	// TODO Auto-generated constructor stub
	JJLOG.println("CommunicationMode constructor");
	//	usingAPAMode = false;
	//	usingSTAMode = false;
	//obj_webSer = new WebserverHandler;
	//ptr_webSer1 = new WebserverHandler;
	//xTaskCreate(WebserverHandler::&websocketLoop, "websocketLoop", 8000, NULL, 5, NULL);
}

CommunicationMode::~CommunicationMode() {
	// TODO Auto-generated destructor stub

}



esp_err_t CommunicationMode::event_handler(void *ctx, system_event_t *event)
{
	char msg_to_serial[32];

	httpd_handle_t *server = (httpd_handle_t *) ctx;

	switch(event->event_id)
	{
		//ap mode
		case SYSTEM_EVENT_AP_STACONNECTED:
		{
			xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);

//			snprintf(
//					msg_to_serial, sizeof(msg_to_serial),
//					MACSTR " join, aid: %d" ,
//					MAC2STR(event->event_info.sta_connected.mac),
//					event->event_info.sta_connected.aid);
//			JJLOG.println(msg_to_serial);
//			JJLOG.printf(
//					msg_to_serial, sizeof(msg_to_serial),
//					MACSTR " join, aid: %d" ,
//					MAC2STR(event->event_info.sta_connected.mac),
//					event->event_info.sta_connected.aid);


			//snprintf ( msg_to_serial, sizeof(msg_to_serial), "ap got ip:%s", ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
			//JJLOG.printf( msg_to_serial, sizeof(msg_to_serial), "ap got ip:%s", ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));

			char macAdd[18];

			snprintf (
					macAdd,
					sizeof(macAdd),
					MACSTR,
					MAC2STR(event->event_info.sta_connected.mac));

			//JJLOG.println(
			JJLOG.println(
					"App MAC Address\t: [" +
					String (event->event_info.sta_connected.aid) + "] " +
					String (macAdd ) );

			for (int jLoop = 0; jLoop < 3; jLoop++)
			{

				jStr fileContain =jobjFileOperation.jreadFile( String ("/user/" + String (jLoop)) .c_str() );
				if (fileContain == "") continue;

				jStr userHardwareID = objJarusAccessories.getValueFromKey(
						fileContain ,
						"hardwareID");

				std::stringstream jStream(userHardwareID);
				jStr token;
				int counter= 0;

				bool flag = true;
				while (getline(jStream,token, ':'))
					if (!	(event->event_info.sta_connected.mac[counter++] == strtol(token.c_str(), 0, 16))	)
						flag  = false;

				if ( flag )
				{

					objJarusAccessories.currentUserToken =
							objJarusAccessories.getValueFromKey(
									fileContain ,
									"token");
					JJLOG.println("App MAC matched : TOKEN Filled");
					break;
				}
			}

			if (*server == NULL) {*server = obj_webSer.start_webserver();}/* Start the web server */
		}
			break;
		case SYSTEM_EVENT_AP_STADISCONNECTED:
			if (*server) {obj_webSer.stop_webserver(*server);*server = NULL;}
			xEventGroupClearBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
			snprintf(msg_to_serial, 32, MACSTR " leave, aid: %d" ,
					MAC2STR(event->event_info.sta_connected.mac),
					event->event_info.sta_connected.aid);

			JJLOG.println(msg_to_serial);
			if (*server) {obj_webSer.stop_webserver(*server);*server = NULL;}
			/* Stop the web server */
			break;

		// station
		case SYSTEM_EVENT_STA_START:
			ESP_ERROR_CHECK(esp_wifi_connect());
			snprintf ( msg_to_serial, sizeof(msg_to_serial), "sta started");
			break;
		case SYSTEM_EVENT_STA_GOT_IP:
			snprintf ( msg_to_serial, sizeof(msg_to_serial), "got ip:%s", ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
			JJLOG.println(msg_to_serial);
			s_retry_num = 0;
			xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
			if (*server == NULL) {*server = obj_webSer.start_webserver();}/* Start the web server */
			break;
		case SYSTEM_EVENT_STA_DISCONNECTED:
			{

				esp_wifi_connect();
				xEventGroupClearBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
				/* Stop the web server */
				if (*server) {obj_webSer.stop_webserver(*server);*server = NULL;}

				//JJLOG.print(".");
				JJLOG.println("connect to ap fail");

				break;
			}
		default:
			break;
    }
    return ESP_OK;
}


void CommunicationMode::jwifi_init_softap_sta_both(void *arg)
{

	//_jserver = &arg;
	s_wifi_event_group = xEventGroupCreate();

	tcpip_adapter_init();

	ESP_ERROR_CHECK( mdns_init() );
	ESP_ERROR_CHECK( mdns_hostname_set(mdnsName.c_str()) );
	ESP_ERROR_CHECK( mdns_instance_name_set(mdnsInstane.c_str()) );
//	ESP_ERROR_CHECK( tcpip_adapter_set_hostname(TCPIP_ADAPTER_IF_STA, mdnsSomethingunk.c_str()	) );


    ESP_ERROR_CHECK(tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP));

    tcpip_adapter_ip_info_t ipAddressInfo;
    memset(&ipAddressInfo, 0, sizeof(ipAddressInfo));
    IP4_ADDR(&ipAddressInfo.ip,10,10,10,1);
    IP4_ADDR(&ipAddressInfo.gw,10,10,10,1);
    IP4_ADDR(&ipAddressInfo.netmask,255,255,255,0);
    ESP_ERROR_CHECK(tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_AP, &ipAddressInfo));

    ESP_ERROR_CHECK(tcpip_adapter_dhcps_start(TCPIP_ADAPTER_IF_AP));

    tcpip_adapter_ip_info_t ipAddressInfo123 = {};
	tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_AP, &ipAddressInfo123);
	char msg_to_serial[32];

	snprintf(msg_to_serial, 32, "My IP:\t" 		IPSTR, IP2STR(&ipAddressInfo123.ip));		JJLOG.println(msg_to_serial);
	snprintf(msg_to_serial, 32, "My Gateway:\t" IPSTR, IP2STR(&ipAddressInfo123.gw));		JJLOG.println(msg_to_serial);
	snprintf(msg_to_serial, 32, "My netMask:\t" IPSTR, IP2STR(&ipAddressInfo123.netmask));	JJLOG.println(msg_to_serial);

	ESP_ERROR_CHECK(esp_event_loop_init(event_handler, arg));
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	//ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));


	// ************ AP config ************ //
	wifi_config_t ap_config = {};
	strcpy	(	(char *) ap_config.ap.ssid,		apa_ssid.c_str()	);
	ap_config.ap.ssid_len = strlen(apa_ssid.c_str());
	strcpy	(	(char *) ap_config.ap.password,	apa_pass.c_str()	);
	ap_config.ap.max_connection = ap_EXAMPLE_MAX_STA_CONN;

	if (strlen(apa_pass.c_str()) == 0)
		ap_config.ap.authmode = WIFI_AUTH_OPEN;
	else
		ap_config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;


	// ************ STA config ************ //
	wifi_config_t sta_config = {};
	strcpy(	(char *)sta_config.sta.ssid,		sta_ssid.c_str()	);
	strcpy(	(char *)sta_config.sta.password,	sta_pass.c_str()	);

	// ************ Configuring Both ************ //
	ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA,	&sta_config));
	ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP,		&ap_config));
	ESP_ERROR_CHECK(esp_wifi_start());

	ESP_LOGI(TAG, "ap ssid %s", 		ap_config.ap.ssid);
	ESP_LOGI(TAG, "ap pass %s", 		ap_config.ap.password);
	ESP_LOGI(TAG, "ap len %d", 			ap_config.ap.ssid_len);
	ESP_LOGI(TAG, "ap max connec%d", 	ap_config.ap.max_connection);
	ESP_LOGI(TAG, "ap auth mode %d", 	ap_config.ap.authmode);
	ESP_LOGI(TAG, "sta ssid %s", 		sta_config.sta.ssid);
	ESP_LOGI(TAG, "sta pass %s", 		sta_config.sta.password);

}

void CommunicationMode::jwifi_init_AP(void *arg)
{
	s_wifi_event_group = xEventGroupCreate();

	tcpip_adapter_init();

//	ESP_ERROR_CHECK( mdns_init() );
//	ESP_ERROR_CHECK( mdns_hostname_set(mdnsName.c_str()) );
//	ESP_ERROR_CHECK( mdns_instance_name_set(mdnsInstane.c_str()) );
//	ESP_ERROR_CHECK( tcpip_adapter_set_hostname(TCPIP_ADAPTER_IF_STA, mdnsSomethingunk.c_str()	) );


    ESP_ERROR_CHECK(tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP));

    tcpip_adapter_ip_info_t ipAddressInfo;
    memset(&ipAddressInfo, 0, sizeof(ipAddressInfo));
    IP4_ADDR(&ipAddressInfo.ip,10,10,10,1);
    IP4_ADDR(&ipAddressInfo.gw,10,10,10,1);
    IP4_ADDR(&ipAddressInfo.netmask,255,255,255,0);
    ESP_ERROR_CHECK(tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_AP, &ipAddressInfo));

    ESP_ERROR_CHECK(tcpip_adapter_dhcps_start(TCPIP_ADAPTER_IF_AP));

    tcpip_adapter_ip_info_t ipAddressInfo123 = {};
	tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_AP, &ipAddressInfo123);
	char msg_to_serial[32];

	snprintf(msg_to_serial, 32, "My IP:\t" 		IPSTR, IP2STR(&ipAddressInfo123.ip));		JJLOG.println(msg_to_serial);
	snprintf(msg_to_serial, 32, "My Gateway:\t" IPSTR, IP2STR(&ipAddressInfo123.gw));		JJLOG.println(msg_to_serial);
	snprintf(msg_to_serial, 32, "My netMask:\t" IPSTR, IP2STR(&ipAddressInfo123.netmask));	JJLOG.println(msg_to_serial);

	ESP_ERROR_CHECK(esp_event_loop_init(event_handler, arg));
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));

	// ************ AP config ************ //
	wifi_config_t ap_config = {};
	strcpy	(	(char *) ap_config.ap.ssid,		apa_ssid.c_str()	);
	ap_config.ap.ssid_len = strlen(apa_ssid.c_str());
	strcpy	(	(char *) ap_config.ap.password,	apa_pass.c_str()	);
	ap_config.ap.max_connection = ap_EXAMPLE_MAX_STA_CONN;

	if (strlen(apa_pass.c_str()) == 0)
		ap_config.ap.authmode = WIFI_AUTH_OPEN;
	else
		ap_config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;

	// ************ Configuring Both ************ //
	ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP,		&ap_config));
	ESP_ERROR_CHECK(esp_wifi_start());

	ESP_LOGI(TAG, "ap ssid %s", 		ap_config.ap.ssid);
	ESP_LOGI(TAG, "ap pass %s", 		ap_config.ap.password);
	ESP_LOGI(TAG, "ap len %d", 			ap_config.ap.ssid_len);
	ESP_LOGI(TAG, "ap max connec%d", 	ap_config.ap.max_connection);
	ESP_LOGI(TAG, "ap auth mode %d", 	ap_config.ap.authmode);

}

void CommunicationMode::jwifi_init_STA(void *arg)
{

	//_jserver = &arg;
	s_wifi_event_group = xEventGroupCreate();

	tcpip_adapter_init();

	ESP_ERROR_CHECK( mdns_init() );
	ESP_ERROR_CHECK( mdns_hostname_set(mdnsName.c_str()) );
	ESP_ERROR_CHECK( mdns_instance_name_set(mdnsInstane.c_str()) );
	ESP_ERROR_CHECK( tcpip_adapter_set_hostname(TCPIP_ADAPTER_IF_STA, mdnsSomethingunk.c_str()	) );

    tcpip_adapter_ip_info_t ipAddressInfo123 = {};
	tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_AP, &ipAddressInfo123);
	char msg_to_serial[32];

	snprintf(msg_to_serial, 32, "My IP:\t" 		IPSTR, IP2STR(&ipAddressInfo123.ip));		JJLOG.println(msg_to_serial);
	snprintf(msg_to_serial, 32, "My Gateway:\t" IPSTR, IP2STR(&ipAddressInfo123.gw));		JJLOG.println(msg_to_serial);
	snprintf(msg_to_serial, 32, "My netMask:\t" IPSTR, IP2STR(&ipAddressInfo123.netmask));	JJLOG.println(msg_to_serial);

	ESP_ERROR_CHECK(esp_event_loop_init(event_handler, arg));
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

	// ************ STA config ************ //
	wifi_config_t sta_config = {};
	strcpy(	(char *)sta_config.sta.ssid,		sta_ssid.c_str()	);
	strcpy(	(char *)sta_config.sta.password,	sta_pass.c_str()	);

	// ************ Configuring Both ************ //
	ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA,	&sta_config));
	ESP_ERROR_CHECK(esp_wifi_start());

	ESP_LOGI(TAG, "sta ssid %s", 		sta_config.sta.ssid);
	ESP_LOGI(TAG, "sta pass %s", 		sta_config.sta.password);

}

