#ifndef SERIAL_COMMUNICATION_H
#define SERIAL_COMMUNICATION_H

#include "json.hpp"
#include "SerialPort.hpp"

#include<iostream>
#include<string>

using json = nlohmann::json;


#define MSG_MAX_SIZE 1024


class SerialCommunication {

public:
	static bool SendToSerial(SerialPort* arduino, json j_msg);
	static bool RcvFromSerial(SerialPort* arduino, std::string& msg);
};



#endif
