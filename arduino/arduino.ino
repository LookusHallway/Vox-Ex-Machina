/*
  arduino.ino
  Author: Luke Hathaway

  Three-Motor Stepper Control with Y2 mirroring Y1 in opposite direction
  Motor 1 (X): STEP=2, DIR=5
  Motor 2 (Y1): STEP=3, DIR=6
  Motor 3 (Y2): STEP=4, DIR=7 (mirrors Motor 2 in opposite direction)
  Enable: shared on pin 8
  LED: ON if any motor is moving (pin 13)
  Serial commands:
    POSITION <motor> <targetPos>
    SPEED <motor> <ms_delay>
    STOP <motor>
*/

#include <AccelStepper.h>

// defines pins numbers
#define ENA 8     // Enable
#define STEPX 5   // Step for top motor (x axis)
#define STEPY1 6  // Step for left motor (y axis)
#define STEPY2 7  // Step for right motor (y axis)
#define DIRX 2    // Direction for top motor (x axis)
#define DIRY1 3   // Direction for left motor (y axis)
#define DIRY2 4   // Direction for right motor (y axis)
#define LED_PIN 13 // On-board LED pin

const int NUM_MOTORS = 3;

AccelStepper stepperX(AccelStepper::DRIVER, STEPX, DIRX);
AccelStepper stepperY1(AccelStepper::DRIVER, STEPY1, DIRY1);
AccelStepper stepperY2(AccelStepper::DRIVER, STEPY2, DIRY2);


bool isRunning[NUM_MOTORS];
long currentPos[NUM_MOTORS];
long targetPos[NUM_MOTORS];

/* Sets the motor's target to pos, considering that Y1 and Y2 move together */
void setPosition(int motor, long pos) {
  if (motor == 1) {
    stepperX.moveTo(pos);
    isRunning[0] = true;
    Serial.println("X moving to " + String(pos)); // Removing these debugging lines might improve efficiency
  } else if (motor == 2) {
    stepperY1.moveTo(pos);
    stepperY2.moveTo(pos);
    isRunning[1], isRunning[2] = true;
    Serial.println("Y1/Y2 moving to " + String(pos));
  } else {
    Serial.println("Invalid motor ID");
  }
}

/*
  Sets the motor's speed to sps, considering that Y1 and Y2 move together
  NOTE: I have this commented out for now until we figure out the algorithm for the mapping
*/
void setSpeed(int motor, float sps) {
  if (sps < 0) {
    Serial.println("Speed must be positive");
    return;
  }

  // if (motor == 1) {
  //   stepperX.setMaxSpeed(3000);
  //   stepperX.setSpeed(sps);
  //   Serial.println("Set X speed to " + String(sps));
  // } else if (motor == 2) {
  //   stepperY1.setMaxSpeed(3000);
  //   stepperY1.setSpeed(sps);
  //   stepperY2.setMaxSpeed(3000);
  //   stepperY2.setSpeed(sps);
  //   Serial.println("Set Y1/Y2 speed to " + String(sps));
  // } else {
  //   Serial.println("Invalid motor ID");
  // }
}

/*
  Stops the specified motor
  NOTE: TBD if we actually need this; I found that things worked fine without it so I commented
  out its execution in processCommand()
*/
void stopMotor(int motor) {
  if (motor == 1) {
    stepperX.stop();
    isRunning[0] = false;
    Serial.println("Stopped X");
  } else if (motor == 2) {
    stepperY1.stop();
    stepperY2.stop()
    isRunning[1], isRunning[2] = false;
    Serial.println("Stopped Y1/Y2");
  } else {
    Serial.println("Invalid motor ID");
  }
}

/* Processes the serial command */
void processCommand(String cmd) {
  cmd.trim();
  cmd.toUpperCase();

  if (cmd.startsWith("POSITION")) {
    // parses the motor and position into motor and pos
    int motor, pos = 0;
    int idx1 = cmd.indexOf(' ');
    int idx2 = cmd.indexOf(' ', idx1 + 1);
    motor = cmd.substring(idx1 + 1, idx2).toInt();
    pos = cmd.substring(idx2 + 1).toInt();
      
    setPosition(motor, pos);
  } else if (cmd.startsWith("SPEED")) {
    // parses the motor and speed into motor and val
    int motor, speed = 0;
    int idx1 = cmd.indexOf(' ');
    int idx2 = cmd.indexOf(' ', idx1 + 1);
    motor = cmd.substring(idx1 + 1, idx2).toInt();
    speed = cmd.substring(idx2 + 1).toInt();
    setSpeed(motor, speed);
  } else if (cmd.startsWith("STOP")) {
    // parses the motor
    int motor = 0;
    int idx1 = cmd.indexOf(' ');
    motor = cmd.substring(idx1 + 1).toInt();
    // stopMotor(motor);
  } else {
    Serial.println("Unknown command.");
  }
}


void setup() {
  Serial.begin(115200);

  // Set enable pins
  stepperX.setEnablePin(ENA);
  stepperY1.setEnablePin(ENA);
  stepperY2.setEnablePin(ENA);

  // Set pin inversions
  stepperX.setPinsInverted(false, false, true);
  stepperY1.setPinsInverted(false, false, true);
  stepperY2.setPinsInverted(true, false, true); // Invert the direction pin so that motors Y1 and Y2 are coordinated

  // Enables outputs
  stepperX.enableOutputs();
  stepperY1.enableOutputs();
  stepperY2.enableOutputs();

  // Zeros each stepper, TBD if we decide to calibrate it
  stepperX.setCurrentPosition(0);
  stepperY1.setCurrentPosition(0);
  stepperY2.setCurrentPosition(0);

  // With current hardware config, keep this because 7000 caused an electrical fire
  stepperX.setMaxSpeed(5000); // DONT CHANGE
  stepperY1.setMaxSpeed(6000); // DONT CHANGE
  stepperY2.setMaxSpeed(6000); // DONT CHANGE

  // Sets acceleration for each motor
  stepperX.setAcceleration(5000);
  stepperY1.setAcceleration(5000);
  stepperY2.setAcceleration(5000);

  // Initial movement for debugging
  stepperX.moveTo(500);
  stepperY1.moveTo(500);
  stepperY2.moveTo(500);

  stepperX.moveTo(0);
  stepperY1.moveTo(0);
  stepperY2.moveTo(0);

  // Sets each array, TBD if we actually need this
  for (int i = 0; i < NUM_MOTORS; i++) {
    isRunning[i] = false;
    currentPos[i] = 0;
    targetPos[i] = 0;
  }

  // Sets LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("3-Motor Controller Ready.");
}

void loop() {
  if (Serial.available() > 0) {
    String inLine = Serial.readStringUntil('\n');
    processCommand(inLine);
  }

  // Runs each motor with the config in setup()
  stepperX.run();
  stepperY1.run();
  stepperY2.run();
}
