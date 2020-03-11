

#define JJLOG Serial

#include <Arduino.h>
#include <iostream>
#include <stdio.h>

#include <iterator>
#include <map>
#include <vector>


typedef std::string jStr;
typedef std::vector<uint16_t> IRContainer;
typedef std::map<jStr, jStr> jsonPair;
typedef std::vector<jStr> jsonNested;

#include <mutex>          // std::mutex
extern std::mutex GlobalMutexLU;           // mutex for critical section

extern jStr cmdFromWebSocket;           // mutex for critical section
extern jStr replyToWebSocket;           // mutex for critical section
extern bool irDisabler;           // mutex for critical section


