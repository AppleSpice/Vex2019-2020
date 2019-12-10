/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// RightWheels          motor         1               
// LeftWheels           motor         2               
// StrafingWheels       motor         3               
// ClawMotor            motor         4               
// LiftMotor            motor         8               
// Controller1          controller                    
// LiftMotor2           motor         7               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  LeftWheels.setVelocity(50, vex::velocityUnits::pct); 
  RightWheels.setVelocity(50, vex::velocityUnits::pct);         //set motors to go forward pushing preload into goal
  LeftWheels.spin(forward), true;
  RightWheels.spin(forward);
  vex::task::sleep(2500);                                       //waits for the motors to go for 2 and a half seconds before becking up
  LeftWheels.setVelocity(50, vex::velocityUnits::pct);
  RightWheels.setVelocity(50, vex::velocityUnits::pct);         //backs motors up away from the goal
  LeftWheels.spin(reverse), true;
  RightWheels.spin(reverse);
  vex::task::sleep(2500);                                      //waits 2 and a half seconds before stoping the motors again
  LeftWheels.stop();
  RightWheels.stop();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
        LeftWheels.spin(directionType::fwd, Controller1.Axis3.value(), velocityUnits::pct);      //    
        RightWheels.spin(directionType::fwd, Controller1.Axis2.value(), velocityUnits::pct);     //main driving  
        StrafingWheels.spin(directionType::fwd, Controller1.Axis4.value(), velocityUnits::pct);  //       

        if(Controller1.ButtonL1.pressing()) {
            ClawMotor.spin(directionType::fwd, 50, velocityUnits::pct); //open claw
        }
        else if(Controller1.ButtonL2.pressing()) {
            ClawMotor.spin(directionType::rev, 50, velocityUnits::pct); //close claw
        }
        else {
            ClawMotor.stop(brakeType::brake);
        }
        if(Controller1.ButtonR1.pressing()) {
            LiftMotor.spin(directionType::fwd, 50, velocityUnits::pct); //lift arm up 
            LiftMotor2.spin(directionType::fwd, 50, velocityUnits::pct); //lift arm up 
        }
        else if(Controller1.ButtonR2.pressing()) {
            LiftMotor.spin(directionType::rev, 50, velocityUnits::pct); //brings arm down
            LiftMotor2.spin(directionType::fwd, 50, velocityUnits::pct); //brings arm down2
        }
        else {
            LiftMotor.stop(brakeType::brake);   
            LiftMotor2.stop(brakeType::brake);     
        }
      

        task::sleep(20);




    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
