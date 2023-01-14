
#include "stepperControl.h"
//#include <algorithm>


stepperControl::stepperControl()
{
	string getIP;		//read IP from user
	int getPort;		//read port from user

	cout << "***********************************************************************" << endl;
	cout << "Please enter a valid IP adress. Press 0 for default IP (192.168.1.102):" << endl;
	cin >> getIP;
	if (getIP == "0") { getIP = "192.168.1.102"; }
	cout << "Got it! Enter a valid port now. Press 0 for default port (1000):" << endl;
	cin >> getPort;
	if (getPort == 0) { getPort = 1000; }

	stepperConnection.linkSocket(getIP, getPort);		//initalize connection to stepper-motor
}


stepperDataReceive stepperControl::getStepperValues()
{
	stepperDataReceive returnData;

	string receivedData = stepperConnection.recvStepperData();		//receive data from stepper-motor

	while (true)
	{
		string receivedData = stepperConnection.recvStepperData();		//receive data from stepper until valid
		if (validateData(receivedData))break;
	}

	returnData.position = strIndexToInt(&receivedData, POSITION_INDEX, POSITION_LENGTH);		//turns a string into an int
	returnData.speed = strIndexToInt(&receivedData, SPEED_INDEX, SPEED_LENGTH);
	returnData.time = strIndexToInt(&receivedData, TIME_INDEX, TIME_LENGTH);

	return returnData;
}


void stepperControl::moveStepper(int speed)
{
	stepperDataSend sendStepperData;
	sendStepperData.speed = max(min(speed, 3000), -3000);		//sets the stepper parameters
	sendStepperData.torque = 8000;
	sendStepperData.acceleration = 2000;
	sendStepperData.decceleration = 2000;
	sendStepperData.mode = 130;		//mode = "PI-Geschwindigkeitsregler"
	sendStepperData.position = 0;		//No use for the position parameter

	if (speed == 0)		//when speed is set to 0, stepper stops
	{
		sendStepperData.mode = 0;		//set stepper to stop
	}

	string XMLOrder = createXMLOrder(sendStepperData);		//convert prarameters to a xml

	stepperConnection.sendStepperData(XMLOrder);		//send data to stepper
}

void stepperControl::printStepperPos()		//while stepper is in motion print params to the console
{
	stepperDataReceive motorData = getStepperValues();
	cout << "position: \t" << (motorData.position / 10) << "\" " << "\tspeed: \t" << motorData.speed << "RPM " << "\ttime: \t" << motorData.time << "ms " << endl;
}

bool stepperControl::validateData(string message)		//validates the TCP string
{
	return ((message[0] == '<') && (message[148] == '/') && (message[149] == '>'));
}

int stepperControl::strIndexToInt(string* dataInput, int startIndex, int length)		//get params from string
{
	string subString = (*dataInput).substr(startIndex, length).data();
	return strtol(subString.data(), nullptr, 10);
}

string stepperControl::createXMLOrder(stepperDataSend toMotor)		//add prefixes to the params received from stepper
{
	return 	("<control pos=\"" + to_string(toMotor.position)
		+ "\" speed=\"" + to_string(toMotor.speed)
		+ "\" torque=\"" + to_string(toMotor.torque)
		+ "\" mode=\"" + to_string(toMotor.mode)
		+ "\" acceleration=\"" + to_string(toMotor.acceleration)
		+ "\" decceleration=\"" + to_string(toMotor.decceleration)
		+ "\" /> ");
}


