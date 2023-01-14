
#include <stdio.h>		//include libraries and header files
#include <iostream>
#include <winsock2.h>
#include <windows.h> 
#include <string>
#include "socketTCP.h"
#include "stepperControl.h"
#include "basicUI.h"

using namespace std;		//defining namespace

stepperControl stepper;		//execute stepper control function
inputCtrl UserInput;		//execute user input control


int main()
{
	while (true)
	{
		if (UserInput.getBtnState())		//get users input and start movement of the stepper motor
		{
			switch (UserInput.getUserInput())
			{
			case stepperStop:		//user stopped the motor
				stepper.moveStepper(0);		//set speed to zero
				UserInput.printUI();		//print mini UI to console
				break;

			case quit:		//user quitted the program
				stepper.moveStepper(0);		//set speed to zero
				break;

			case stepperFwd:		//user stroke forward button
				stepper.moveStepper(2000);		//set speed to 2000
				break;

			case stepperBwd:		//user stroke backward button
				stepper.moveStepper(-2000);		//set speed to -2000
				break;
			}
		}

		if ((UserInput.getUserInput() == stepperFwd) || (UserInput.getUserInput() == stepperBwd))		//print information to the console while stepper is moving
		{
			stepper.printStepperPos();
		}

		if (UserInput.getUserInput() == quit)		//exit progrom if requested by user
		{
			break;
		}
	}
}