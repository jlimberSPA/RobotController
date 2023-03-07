// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Controller2.ino
    Created:	3/4/2023 2:05:33 PM
    Author:     JOE-HP-LAPTOP\jmlma
*/



#include "Robot_Controller.h"
// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//
using namespace controller_namespace;
controller_namespace::Robot_Controller myController = controller_namespace::Robot_Controller();
// The setup() function runs once each time the micro-controller starts
void setup()
{
    myController.ControllerSetup();

}

// Add the main program code into the continuous loop() function
void loop()
{
    myController.ControllerLoop();

}
