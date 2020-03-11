// need to rethink all

///*#define str(x) String(x)
//
//#define _save_current_status_(log_msg) saveStatus(str(__DATE__), str(__TIME__), str(FPSTR(__FILE__)), str(FPSTR(__func__)), String(__LINE__), log_msg);
//#define _file_related_issue_(filename) file_issue(str(__DATE__), str(__TIME__), str(FPSTR(__FILE__)), str(FPSTR(__func__)), String(__LINE__), filename);
//#define _general_issue_(issue_details) file_issue(str(__DATE__), str(__TIME__), str(FPSTR(__FILE__)), str(FPSTR(__func__)), String(__LINE__), issue_details);
//
//////eERROR, eWarning, eLOG, efunc, efileNotOpen
//#define j_RELEASE 0
//#define j_DEBUG   1
//
//#define MODE j_DEBUG    //j_RELEASE, j_DEBUG
//
//#if MODE==j_DEBUG
//  #define jdebug(errorCode, msg) debug_msg(String(FPSTR(__FILE__)), String(FPSTR(__func__)), String(FPSTR(__LINE__)), errorCode, msg);
//#elif MODE==j_RELEASE
//  #define jdebug(errorCode, errorMsg)
//#endif
//
//
//#include "FS.h"
///*
//extern "C"
//{
//  #include <user_interface.h>
//}
//*/
//
//String getValueBySplit(String data, char separator, int index)
//{
//  int found = 0;
//  int strIndex[] = {0, -1};
//  int maxIndex = data.length()-1;
//
//  for(int i=0; i<=maxIndex && found<=index; i++){
//    if(data.charAt(i)==separator || i==maxIndex){
//        found++;
//        strIndex[0] = strIndex[1]+1;
//        strIndex[1] = (i == maxIndex) ? i+1 : i;
//    }
//  }
//  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
//}
//String getCurrentFileName(String full_file_address)
//{
//  for (int myloop = 0; myloop < 20; myloop++ )
//  {
//    if (getValueBySplit(full_file_address, (char)47, myloop).equals("") && (myloop != 0) )
//    {
//      return getValueBySplit(full_file_address, (char)47, myloop-1);
//    }
//  }
//
//}
//
//enum errorEnum
//{
//  eERROR,
//  eWarning,
//  eLOG,
//  efunc,
//  efileNotOpen
//};
//
//void debug_msg(String file, String func, String line, int errorCode, String msg)
//{
//
//  #ifdef j_DEBUG
//
//    switch ( errorCode )
//    {
//      case efileNotOpen:      // cant run next
//      {
//        JJLOG.println("file open error");
//        //action save to file
//        msg = file + ":"+ func + ":"+ line +":"+ msg;
//      }break;
//
//      case eERROR:      // cant run next
//      {
//        msg = file + ":"+ func + ":"+ line +":"+ msg;
//      }break;
//
//      case eLOG:       // just log message
//      {
//        msg = msg;
//      }break;
//
//      case eWarning:       // warning
//      {
//        msg = line +":"+ msg;
//      }break;
//      case efunc:       // warning
//      {
//        msg = "fun:-" + func +":"+ msg;
//      }break;
//
//
//      default:
//      {
//        msg = String(errorCode) + ":" + msg;
//      }
//
//    }
//
//    JJLOG.println(msg);
//    if (errorCode == eERROR) while(1);
//  #endif
//
//}
//
//
//
//bool isLastReset_has_problem()
//{
//  struct rst_info *rtc_info = system_get_rst_info();
//  return ( (rtc_info->reason == REASON_DEFAULT_RST)  || (rtc_info->reason == REASON_EXT_SYS_RST) ) ?  false : true;
//}
//
//
////saveStatus
//void saveStatus(String jdate, String jtime, String jfileName, String jfunc, String line, String msg)
//{
//  warning_indicator = true;
//  String toSave = "[ " +jdate + " " + jtime +"] "+ getCurrentFileName(jfileName) +" "+ jfunc + " ln." + line +" " +msg;
//
//  File f1 = SPIFFS.open(last_action_before_shutdown, "w+");
//  if (!f1)
//  {
//    /*webSocket.broadcastTXT("undefine error");*/
//    JJLOG.println("file open failed");
//  }
//  f1.print(toSave);
//  f1.close();
//
//}
//
//String get_last_reset_data()
//{
//  warning_indicator = true;
//  struct rst_info *rtc_info = system_get_rst_info();
//
//  String lastResetReason = "";
//  switch (rtc_info->reason)
//  {
//    case REASON_DEFAULT_RST       : lastResetReason = "DEFAULT_RST";     break;
//    case REASON_WDT_RST           : lastResetReason = "WDT_RST";         break;
//    case REASON_EXCEPTION_RST     : lastResetReason = "EXCEPTION_RST";   break;
//    case REASON_SOFT_WDT_RST      : lastResetReason = "SOFT_WDT_RST";    break;
//    case REASON_SOFT_RESTART      : lastResetReason = "SOFT_RESTART";    break;
//    case REASON_DEEP_SLEEP_AWAKE  : lastResetReason = "DEEP_SLEEP_AWAKE";break;
//    case REASON_EXT_SYS_RST       : lastResetReason = "EXT_SYS_RST";     break;
//  }
//  //https://arduino-esp8266.readthedocs.io/en/latest/exception_causes.html
//  //rst_info->exccause
//
//  lastResetReason += ", ";
//  //lastResetReason += "exccause " + String(rst_info->exccause    , DEC) + ", ";  not working need to solve in future
//  lastResetReason += "epc1 " + String(rtc_info->epc1    , HEX) + ", ";
//  lastResetReason += "epc2 " + String(rtc_info->epc2    , HEX) + ", ";
//  lastResetReason += "epc3 " + String(rtc_info->epc3    , HEX) + ", ";
//  lastResetReason += "excvaddr " + String(rtc_info->excvaddr, HEX) + ", ";
//  lastResetReason += "depc " + String(rtc_info->depc    , HEX) + ", ";
//  lastResetReason += "exccause " + String(rtc_info->exccause    , HEX) + ", ";
//
//  return lastResetReason;
//}
//
//
//void file_issue(String jdate, String jtime, String jfileName, String jfunc, String line, String fileName)
//{
//  warning_indicator = true;
//  String toSave = "file error:- [ " +jdate + " " + jtime +"] "+ getCurrentFileName(jfileName) +" "+ jfunc + " ln." + line +" filename:" + fileName;
//
//  File myFile = SPIFFS.open(warning_saved_file, "a+");
//  if (!myFile)
//  {
//    _save_current_status_("error file can't edit")
//  }
//  myFile.println(toSave);
//  myFile.close();
//}
//
//void general_issue(String jdate, String jtime, String jfileName, String jfunc, String line, String issueName)
//{
//  warning_indicator = true;
//  String toSave = "[ " +jdate + " " + jtime +"] "+ getCurrentFileName(jfileName) +" "+ jfunc + " ln." + line +" issue:" + issueName;
//
//  File myFile = SPIFFS.open(warning_saved_file, "a+");
//  if (!myFile)
//  {
//    _save_current_status_("general issue")
//  }
//  myFile.println(toSave);
//  myFile.close();
//}
//
//
//String jreadfile(String filename) {
//  String readText = "";
//  File myFile = SPIFFS.open(filename, "r");
//  if (!myFile)
//  {
//    JJLOG.println("problem reading file " + filename);
//   /*broadcastTXT() something*/
//  }
//  while (myFile.available()) {
//    readText += (char) myFile.read();
//    //JJLOG.write(myFile.read());                    // Read all the data from the file and display it
//  }
//  myFile.close();
//  return readText;
//}
//*/
