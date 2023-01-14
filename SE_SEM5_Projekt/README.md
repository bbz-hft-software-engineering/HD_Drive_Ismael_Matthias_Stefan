# Project Title

Stepper motor driver (TCP)

## Description

This project is designed to controll a stepper motor which provides a simple webserver throu a TCP socket. The program code is written in C++.

## Getting Started

### Dependencies

* [Windows](https://www.microsoft.com/windows/) 10 or 11 
* IDE [VisualStudio Community](https://visualstudio.microsoft.com/de/downloads/)

### Installing

* No install required. Run the program in the debug console.

### Executing program

* Run the program in the debug console

## Userguide
* Once you started the program you are prompted to enter an IP adress. If you want to use the default adress press "0".
* Next you are asked to enter a Port. If you want to use the default Port, press "0".
* Next a basic UI which looks like the following is printed to the console window.

* ***********                    CONTROLS                      **********
* **                                                                   **
* **            FORWARD          BACKWARDS           QUIT              **
* **                                                                   **
* **            ||>>>||           ||<<<||           ||***||            **
* **            || W ||           || S ||           || A ||            **
* **            ||___||           ||___||           ||___||            **
* **                                                                   **
* **             As the stepper is in rotation its params              **
* **      are read out via TCP and printed in this console window      **

* Have Fun!

## Help

* Contact authors if you need assistance

## Authors

[Stefan Waskow](stefan.waskow@bbz-sh.ch)
[Matthias Hättich](matthias.haettich@bbz-sh.ch)
[Ismael Paganini](ismael.paganini@bbz-sh.ch)

## Version History

* 0.1
    * Initial Release
