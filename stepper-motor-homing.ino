#include <AccelStepper.h>

const int homeSwitch = 8;

AccelStepper stepper(1, 2, 3);

long travelX;
int moveFinished = 1;
long initialHoming = -1;

void setup() {
  Serial.begin(9600);

  pinMode(homeSwitch, INPUT_PULLUP);

  delay(5);

  stepper.setMaxSpeed(100);

  stepper.setAcceleration(100);

  Serial.print("Stepper is Homing . . . . . . ");

  while (digitalRead(homeSwitch)) {
    stepper.moveTo(initialHoming);
    initialHoming--;
    stepper.run();
    delay(5);
  }
  stepper.setCurrentPosition(0);
  stepper.setMaxSpeed(100.0);
  stepper.setAcceleration(100.0);
  initialHoming = 1;

  while (!digitalRead(homeSwitch)) {
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
  while (Serial.available() > 0) {

    moveFinished = 0;
    travelX = Serial.parseInt();

    if (travelX < 0 || travelX > 1350) {
      Serial.println("");
      Serial.println("Please enter a value greater than zero and smaller or equal to 1350.....");
      Serial.println("");
    } else {
      Serial.print("Moving stepper into position: ");
      Serial.println(travelX);

      stepper.moveTo(travelX);
      delay(1000);
    }
  }

  if (travelX >= 0 && travelX <= 1350) {
    if ((stepper.distanceToGo() != 0)) {
      stepper.run();
    }

    if ((moveFinished == 0) && (stepper.distanceToGo() == 0)) {
      Serial.println("COMPLETED!!");
      Serial.println("");
      Serial.println("Enter Travel distance (Positive for CW / Negative for CCW and Zero for back to Home): ");
      moveFinished = 1;
    }
  }
}







