#pragma once
#include <windows.h>		//include libraries and header files
#include <iostream>
#include <string>

using namespace std;		//defining namespace

enum btnState		//definig possible key presses
{
	undef,
	stepperStop,
	quit,
	stepperFwd,
	stepperBwd
};

class inputCtrl
{
public:
	const char btnFwd = 'W';		//defining the input buttons
	const char btnStop = 'D';
	const char btnBwd = 'S';
	const char btnQuit = 'A';

	bool getBtnState();		//checking for inputs

	btnState getUserInput();		//return the last stroked key
	
	void printUI();		//prints a short instruciton to the console window

private:
	btnState activeBtn = undef;
};

