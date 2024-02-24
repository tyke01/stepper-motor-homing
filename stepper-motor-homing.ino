#include <AccelStepper.h>

const int homeSwitch = 8;

AccelStepper stepper(1, 2, 3); //1 = Easy Driver interface,  MEGA Pin 2 connected to STEP pin of Driver, MEGA Pin 3 connected to DIR pin of driver

long travelX; // Used to store the travel value entered in the Serial Monitor.

int moveFinished = 1; // check if move is completed

long initialHoming = -1; // home the stepper at startup
 
void setup() {

  Serial.begin(9600);

  pinMode(homeSwitch, INPUT_PULLUP);

  delay(5);

  stepper.setMaxSpeed(100);

  stepper.setAcceleration(100);

  Serial.print("Stepper is Homing . . . . . . ");

  while (digitalRead(homeSwitch)) {
    // stepper to move CCW until the switch is activated
    stepper.moveTo(initialHoming);

    initialHoming--; //Decrease by 1 for the next move if needed

    stepper.run();

    delay(5);

  }
  stepper.setCurrentPosition(0);

  stepper.setMaxSpeed(100.0);

  stepper.setAcceleration(100.0);

  initialHoming = 1;

  while (!digitalRead(homeSwitch)) {
    // make the stepper move CW until the switch is deactivated 
    stepper.moveTo(initialHoming);

    stepper.run();

    initialHoming++;

    delay(5);
  }

  stepper.setCurrentPosition(0);

  Serial.println("Homing Completed");

  Serial.println("");

  stepper.setMaxSpeed(1000);

  stepper.setAcceleration(1000);

  Serial.println("Enter Travel distance (Positive for CW / Negative for CCW and Zero for back to Home): ");

}



void loop() {
  // check if values are available in the serial buffer
  while (Serial.available() > 0) {

    moveFinished = 0;

    travelX = Serial.parseInt(); // put numeric value from buffer in the travelX variable

    if (travelX < 0 || travelX > 1350) {

      //make sure the position entered is not beyond the home or max position.

      Serial.println("");

      Serial.println("Please enter a value greater than zero and smaller or equal to 1350.....");

      Serial.println("");

    } else {

      Serial.print("Moving stepper into position: ");

      Serial.println(travelX);

      stepper.moveTo(travelX); // set the new moveto position of the stepper

      delay(1000);
    }
  }

  if (travelX >= 0 && travelX <= 1350) {

    //  check if the stepper has reached desired position
    if ((stepper.distanceToGo() != 0)) {

      stepper.run(); // move the stepper into position

    }

    // if the move is completed, display the message on the serial monitor

    if ((moveFinished == 0) && (stepper.distanceToGo() == 0)) {

      Serial.println("COMPLETED!!");

      Serial.println("");

      Serial.println("Enter Travel distance (Positive for CW / Negative for CCW and Zero for back to Home): ");

      moveFinished = 1;

    }
  }
}







