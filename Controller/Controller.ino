/*
    Name:       Controller.ino
    Created:	3/4/2023 2:05:33 PM
    Author:     JOE-HP-LAPTOP\jmlma
*/


#include "Robot_Controller.h"

using namespace controller_namespace;
controller_namespace::Robot_Controller myController = controller_namespace::Robot_Controller();
void setup()
{
    myController.ControllerSetup();
}
void loop()
{
    myController.ControllerLoop();
}
