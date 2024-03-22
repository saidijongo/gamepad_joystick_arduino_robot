const int motor_right_p = 3;
const int motor_right_n = 4;

const int motor_left_p = 5;
const int motor_left_n = 6;

const int joystick_x = A0;
const int joystick_y = A1;
const int joystick_threshold = 256;

// setup() is run only one at the beginning.
void setup()
{
    // The motor pins are OUTPUTs
    pinMode(motor_left_p, OUTPUT);
    pinMode(motor_left_n, OUTPUT);  
    pinMode(motor_right_p, OUTPUT);
    pinMode(motor_right_n, OUTPUT);

    // The sensor are INPUTs
    pinMode(joystick_x, INPUT);
    pinMode(joystick_y, INPUT);
}

// the loop() keeps running continuously as long as the Arduino is connected to a power supply.
void loop()
{
    // We query the joystick and store its 'x' and 'y' coordinates. Since 512 represents the
    // 'center' position of the joystick we subtract that value from the reading to get the
    // required direction of movement.
    // 
    // For instance, is the y-location of the joystick runs out to be negative we know that the
    // robot should move backwards. Similarly, a positive value will indicate a forward motion.
    int x_location = analogRead(joystick_x);
    int y_location = analogRead(joystick_y);

    // We first check if the joystick has been moved "far enough" from the mean position to trigger
    // the movement.
    if (abs(y_location) > threshold)
    {
        // we next check the direction of movement and move the robot in that direction.
        if (y_location > 0)
        {
            motor_left('F');
            motor_right('F');
            delay(50);
        }
        else if (y_location < 0)
        {
            motor_left('B');
            motor_right('B');
            delay(50);
        }
    }
    // we do the same with the x axes.
    else if (abs(x_location) > threshold)
    {
        // we next check the direction of movement and move the robot in that direction.
        if (x_location > 0)
        {
            motor_left('F');
            motor_right('B');
            delay(50);
        }
        else if (x_location < 0)
        {
            motor_left('B');
            motor_right('F');
            delay(50);
        }
    }
}

/*
 * The next two functions control the left/right motors.
 *   'F' - Moves a motor forward.
 *   'B' - Moves a motor backward.
 *   'S' - Stops the motor.
 *
 * The forward and backward motions of the robot are trivial. Both the motors need to go forward and
 * backward. We can introduce clockwise and anti-clockwise motions in our robot by turning one wheel
 * forward and the other backward. For example if the left motor goes forward and the right one
 * backward, our robot will turn clockwise and vice versa.
 * 
 */

void motor_left(char dir)
{
  switch(dir)
  {
    case 'F':
      digitalWrite(motor_left_p, HIGH);
      digitalWrite(motor_left_n, LOW);
      break;
    case 'B':
      digitalWrite(motor_left_p, LOW);
      digitalWrite(motor_left_n, HIGH);
      break;
    case 'S':
      digitalWrite(motor_left_p, HIGH);
      digitalWrite(motor_left_n, HIGH);
      break;
  }
}

void motor_right(char dir)
{
  switch(dir)
  {
    case 'F':
      digitalWrite(motor_right_p, LOW);
      digitalWrite(motor_right_n, HIGH);
      break;
    case 'B':
      digitalWrite(motor_right_p, HIGH);
      digitalWrite(motor_right_n, LOW);
      break;
    case 'S':
      digitalWrite(motor_right_p, HIGH);
      digitalWrite(motor_right_n, HIGH);
      break;
  }
}
