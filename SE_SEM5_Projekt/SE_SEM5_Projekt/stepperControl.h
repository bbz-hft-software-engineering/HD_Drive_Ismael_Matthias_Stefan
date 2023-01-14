#pragma once
#include <string>		//include libraries and header files
#include <winsock2.h>
#include "socketTCP.h"
#include <iostream>

using namespace std;		//defining namespace

struct stepperDataReceive		//defining structs
{
	int position;
	int speed;
	int time;
};

struct stepperDataSend
{
	int position;
	int speed;
	int torque;
	int acceleration;
	int decceleration;
	int mode;
};


class stepperControl
{

public:		//constructor

	stepperControl();		//connect to motor. Ask for Ip and Port

	stepperDataReceive getStepperValues();		//receives data from the tcp socekt and turns them into a struct of motor values

	void moveStepper(int speed);		//set stepper-motor to forward or backward movement

	void printStepperPos();		//print the current stepper-motor parameters to the console window

private:
	const int POSITION_INDEX = 22;		//defeinition of the received XML string with index and lenght of the parameters
	const int POSITION_LENGTH = 10;
	const int SPEED_INDEX = 41;
	const int SPEED_LENGTH = 8;
	const int TIME_INDEX = 136;
	const int TIME_LENGTH = 10;

	socketTCP stepperConnection;		//TCP socket instance

	bool validateData(string);		//checks if the data from the TCP socket is vald

	int strIndexToInt(string* dataInput, int startIndex, int length);		//turns a string into an int

	string createXMLOrder(stepperDataSend);		//turns the stepper parameters to an XML 
};

