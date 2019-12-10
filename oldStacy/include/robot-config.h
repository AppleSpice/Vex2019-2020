using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor RightWheels;
extern motor LeftWheels;
extern motor StrafingWheels;
extern motor ClawMotor;
extern motor LiftMotor;
extern controller Controller1;
extern motor LiftMotor2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );