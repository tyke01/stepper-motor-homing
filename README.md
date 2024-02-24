# stepper-motor-homing

## Stepper Motor Control with AccelStepper Library

This Arduino code utilizes the AccelStepper library to control a stepper motor. The motor is homed at startup and then moved to the desired position based on user input through the Serial Monitor.

### Code Overview

The code begins with the inclusion of the AccelStepper library and defines the pin connected to the home switch (`homeSwitch`). An AccelStepper object (`stepper`) is created to control the stepper motor using the Easy Driver interface.

The code initializes Serial communication, configures the home switch pin as an input with a pull-up resistor, and sets the maximum speed and acceleration of the stepper motor.

During setup, the stepper motor is homed by moving it counterclockwise (CCW) until the home switch is activated and then clockwise (CW) until the switch is deactivated.

In the loop, the code waits for user input through the Serial Monitor. Users can input a desired travel distance (positive for clockwise movement, negative for counterclockwise movement, and zero to return to the home position).

The code checks if the entered position is within bounds and if the motor has reached the desired position. Upon completion, a message is displayed in the Serial Monitor, and users can enter a new travel distance.

### Functionality

- **Homing**: The stepper motor is homed at startup by moving it CCW until the home switch is activated and then CW until the switch is deactivated.
- **User Input**: Users can input a desired travel distance through the Serial Monitor. Positive values move the motor clockwise, negative values move it counterclockwise, and zero returns it to the home position.
- **Position Control**: The code ensures that the entered position is within bounds and moves the motor to the specified position. It checks if the motor has reached the desired position and displays a completion message in the Serial Monitor.

### Usage

1. **Hardware Setup**: Connect the stepper motor to the Arduino with the Easy Driver interface. Connect the home switch to the specified pin (e.g., pin 8).
2. **Upload Code**: Upload the provided Arduino code to the Arduino board.
3. **Serial Monitor**: Open the Serial Monitor to input travel distances and monitor the motor movement and status.
