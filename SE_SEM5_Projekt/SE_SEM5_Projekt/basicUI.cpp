#include "basicUI.h"		//include header file

bool inputCtrl::getBtnState()		//checks for a new input
{
	btnState lastactiveBtn = activeBtn;

	activeBtn = stepperStop;		//initial state for stepper motor

	if (GetAsyncKeyState(btnBwd) & 0x8000)		//checks for backward input
	{
		activeBtn = stepperBwd;
	}

	if (GetAsyncKeyState(btnFwd) & 0x8000)		//checks for forward input
	{
		activeBtn = stepperFwd;
	}

	if (GetAsyncKeyState(btnQuit) & 0x8000)		//checks for quit input
	{
		activeBtn = quit;
	}

	return ((activeBtn != undef) && (activeBtn != lastactiveBtn));		//true if new, undefined input is detected
}

btnState inputCtrl::getUserInput()		//reads the last pressed button
{
	return activeBtn;
}

void inputCtrl::printUI()		//small mini UI and guide for the user
{
	cout << "**********                     CONTROLS                      **********" << endl;
	cout << "**                                                                   **" << endl;
	cout << "**            FORWARD          BACKWARDS           QUIT              **" << endl;
	cout << "**                                                                   **" << endl;
	cout << "**            ||>>>||           ||<<<||           ||***||            **" << endl;
	cout << "**            || " << btnFwd << " ||           || " << btnBwd << " ||           || " << btnQuit << " ||            **" << endl;
	cout << "**            ||___||           ||___||           ||___||            **" << endl;
	cout << "**                                                                   **" << endl;
	cout << "**             As the stepper is in rotation its params              **" << endl;
	cout << "**      are read out via TCP and printed in this console window      **" << endl;
}