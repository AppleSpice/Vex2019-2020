#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor RightWheels = motor(PORT1, ratio18_1, true);
motor LeftWheels = motor(PORT2, ratio18_1, false);
motor StrafingWheels = motor(PORT3, ratio18_1, false);
motor ClawMotor = motor(PORT4, ratio18_1, false);
motor LiftMotor = motor(PORT8, ratio36_1, true);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variables used for controlling motors based on controller inputs
bool Controller1RightShoulderControlMotorsStopped = true;
bool Controller1UpDownButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_callback_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    // check the ButtonR1/ButtonR2 status to control LiftMotor
    if (Controller1.ButtonR1.pressing()) {
      LiftMotor.spin(forward);
      Controller1RightShoulderControlMotorsStopped = false;
    } else if (Controller1.ButtonR2.pressing()) {
      LiftMotor.spin(reverse);
      Controller1RightShoulderControlMotorsStopped = false;
    } else if (!Controller1RightShoulderControlMotorsStopped) {
      LiftMotor.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1RightShoulderControlMotorsStopped = true;
    }
    // check the Up/Down Buttons status to control ClawMotor
    if (Controller1.ButtonUp.pressing()) {
      ClawMotor.spin(forward);
      Controller1UpDownButtonsControlMotorsStopped = false;
    } else if (Controller1.ButtonDown.pressing()) {
      ClawMotor.spin(reverse);
      Controller1UpDownButtonsControlMotorsStopped = false;
    } else if (!Controller1UpDownButtonsControlMotorsStopped){
      ClawMotor.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1UpDownButtonsControlMotorsStopped = true;
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_callback_Controller1);
}