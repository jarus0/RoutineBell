//jarus



void initiate()
{

	//JJLOG.begin(115200, SERIAL_8N1, RXD2, TXD2);
	JJLOG.begin(115200);
	while (!JJLOG) {vTaskDelay(250);}

	JJLOG.println("Device Started");

	if(!SPIFFS.begin())JJLOG.println("SPIFFS Mount Failed");
	    else JJLOG.println("SPIFFS Mount succesful");

}

void print_reset_reason(RESET_REASON reason)
{
  switch ( reason)
  {
    case 1 : JJLOG.print ("POWERON_RESET");break;          /**<1, Vbat power on reset*/
    case 3 : JJLOG.print ("SW_RESET");break;               /**<3, Software reset digital core*/
    case 4 : JJLOG.print ("OWDT_RESET");break;             /**<4, Legacy watch dog reset digital core*/
    case 5 : JJLOG.print ("DEEPSLEEP_RESET");break;        /**<5, Deep Sleep reset digital core*/
    case 6 : JJLOG.print ("SDIO_RESET");break;             /**<6, Reset by SLC module, reset digital core*/
    case 7 : JJLOG.print ("TG0WDT_SYS_RESET");break;       /**<7, Timer Group0 Watch dog reset digital core*/
    case 8 : JJLOG.print ("TG1WDT_SYS_RESET");break;       /**<8, Timer Group1 Watch dog reset digital core*/
    case 9 : JJLOG.print ("RTCWDT_SYS_RESET");break;       /**<9, RTC Watch dog Reset digital core*/
    case 10 : JJLOG.print ("INTRUSION_RESET");break;       /**<10, Instrusion tested to reset CPU*/
    case 11 : JJLOG.print ("TGWDT_CPU_RESET");break;       /**<11, Time Group reset CPU*/
    case 12 : JJLOG.print ("SW_CPU_RESET");break;          /**<12, Software reset CPU*/
    case 13 : JJLOG.print ("RTCWDT_CPU_RESET");break;      /**<13, RTC Watch dog Reset CPU*/
    case 14 : JJLOG.print ("EXT_CPU_RESET");break;         /**<14, for APP CPU, reseted by PRO CPU*/
    case 15 : JJLOG.print ("RTCWDT_BROWN_OUT_RESET");break;/**<15, Reset when the vdd voltage is not stable*/
    case 16 : JJLOG.print ("RTCWDT_RTC_RESET");break;      /**<16, RTC Watch dog reset digital core and rtc module*/
    default : JJLOG.print ("NO_MEAN");
  }
  JJLOG.println();
}


void device_info()
{
    JJLOG.println();
    JJLOG.println(F("Company\t\t: Avinashi Ventures Pvt Ltd"));
    JJLOG.print(F("Firmware\t: Comfortick_"));
    JJLOG.println(objJarusAccessories.jfirmwareVer.c_str());
    JJLOG.print(F("Date\t\t: "));
    JJLOG.println(__DATE__);
    JJLOG.print(F("Time\t\t: "));
    JJLOG.println(__TIME__);
    JJLOG.println("Designer\t: Jaydip Chabhadiya (IoTick Team Leader)");
    JJLOG.println("Coder\t\t: " + String ($$$$$) );
    JJLOG.println();

    JJLOG.println("-------------------------------------- Files Available --------------------------------------");
    jobjFileOperation.jlistDir("/", 0);	//listDir(SPIFFS, "/", 0);
    JJLOG.println();
    JJLOG.print(F("ESP Device id     : "));
    JJLOG.println(objJarusAccessories.str_chipID);

    JJLOG.print("CPU0 reset reason : ");      print_reset_reason(rtc_get_reset_reason(0));
    JJLOG.print("CPU1 reset reason : ");      print_reset_reason(rtc_get_reset_reason(1));

    JJLOG.print(F("ESP Free RAM      : "));    JJLOG.print(ESP.getFreeHeap());    JJLOG.println();
    JJLOG.print(F("Used KB           : "));    JJLOG.print(SPIFFS.usedBytes());   JJLOG.println(F(" KB"));
    JJLOG.print(F("Total KB          : "));    JJLOG.print(SPIFFS.totalBytes());  JJLOG.println(F(" KB"));
    JJLOG.println("\n\n");

}
