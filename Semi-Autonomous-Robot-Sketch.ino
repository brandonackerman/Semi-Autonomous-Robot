// Final Project - Semi-Autonomous Robot
// Brandon Ackerman, RBT173

// GLOBAL VARIABLES
// Motor Control

// define pins used for right motor control
int rightEn = 3;  // right motor enable
int forRight = 4; // right motor forwards
int revRight = 5; // right motor reverse

// define pins used for left Motor Control
int leftEn = 6;  // left motor enable
int forLeft = 7; // left motor forwards
int revLeft = 8; // left motor reverse

// Temperature Sensor
int pinTemp = A1;   // assign analog 1 as the temp sensor
int maxTemp = (75); // define the maximum cutoff temp for shutdown
int appTemp = (65); // define the temp at which the motors will begin slowing down
int temp = 0;       // create an integer to store temperature value

////////////////////////////////////////

// Setup Code
void setup()
{
    // define right motor pins as output
    pinMode(rightEn, OUTPUT);
    pinMode(forRight, OUTPUT);
    pinMode(revRight, OUTPUT);

    // define left motor pins as output
    pinMode(leftEn, OUTPUT);
    pinMode(forLeft, OUTPUT);
    pinMode(revLeft, OUTPUT);

    Serial.begin(9600); // Start the serial monitor
}

// Main Code
void loop()
{
    readTemp(); // read the temperature
                // if the temperature is greater than or equal to the minimum start slowdown threshold,
                //  and less than the maximum threshold,
    if ((temp >= appTemp) && (temp < maxTemp))
    {
        analogWrite(rightEn, 255 - 1); // progressively slow down right motor using PWM
        analogWrite(leftEn, 255 - 1);  // progressively slow down left motor using PWM
        Serial.println("slowing down");
    }

    if (temp >= maxTemp) // if the tempature reading is greater than or equal to the maximum threshold(75c)

        tooHot(); // run function tooHot()

    else
    {
        analogWrite(rightEn, 255); // send full speed PWM command to right motor to enable
        analogWrite(leftEn, 255);  // send full speed PWM command to right motor to enable
        forward();                 // run the forward function
        delay(500);                // wait 500ms
    }
}

// MOTOR SUB-FUNCTIONS

// Right Motor Forward
void rightFor()
{
    digitalWrite(revRight, LOW);  // set arduino pin 5 to LOW - denies power to L293 input2
    digitalWrite(forRight, HIGH); // set arduino pin 4 to HIGH - applies power to L293 input1
}

// Right Motor Reverse
void rightRev()
{
    digitalWrite(revRight, HIGH); // set arduino pin 5 to HIGH - applies power to L293 input2
    digitalWrite(forRight, LOW);  // set arduino pin 4 to LOW - denies power to L293 input1
}

// Left Motor Forward
void leftFor()
{
    digitalWrite(revLeft, LOW);  // set arduino pin 8 to LOW - denies power to L293 input4
    digitalWrite(forLeft, HIGH); // set arduino pin 7 to HIGH - applies power to L293 input3
}

// Left Motor Reverse
void leftRev()
{
    digitalWrite(revLeft, HIGH); // set arduino pin 8 to HIGH - applies power to L293 input4
    digitalWrite(forLeft, LOW);  // set arduino pin 7 to LOW - denies power to L293 input3
}

// MAIN FUNCTIONS

//  Drive Forward
void forward()
{
    Serial.println("driving forward");
    rightFor(); // run the right motor forward function
    leftFor();  // run the left motor forward function
}

// Drive Backwards
void reverse()
{
    Serial.println("driving backwards");
    rightRev(); // run the right motor reverse function
    leftRev();  // run the left motor reverse function
}

// Turn Right
void rightTurn()
{
    Serial.println("turning right");
    leftFor(); // run the left motor forward function
}

// Turn Left
void leftTurn()
{
    Serial.println("turning left");
    rightFor(); // run the right motor forward function
}

// Spin Left
void leftSpin()
{
    Serial.println("spin left");
    rightFor(); // run the right motor forward function
    leftRev();  // run the left motor reverse function
}

// Spin Right
void rightSpin()
{
    Serial.println("spin right");
    leftFor();  // run the left motor forward function
    rightRev(); // run the right motor reverse function
}

// function to immediately stop the car
void killSwitch()
{
    Serial.println("Maximum temperature threshold reached, stopping motors.");
    analogWrite(rightEn, 0); // disable right motor
    analogWrite(leftEn, 0);  // disable left motor
}

// Function to read the temperature
void readTemp()
{
    Serial.println("reading temperature");
    temp = analogRead(pinTemp);           // Read the analog pin
    temp = (temp * 5.0 * 100.0) / 1024.0; // convert output (mv) to readable celcius

    // print the temperature status
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println("C");
}

// function to run when upper temperature limit is reached
void tooHot()
{
    killSwitch(); // run the killswitch function
    delay(2000);  // wait 2 seconds
    {

        analogWrite(rightEn, 128); // enable right motor 1/2 speed
        analogWrite(leftEn, 128);  // enable left motor 1/2 speed
        reverse();                 // run the reverse function
        delay(5000);               // wait 5 seconds (reverse for 5 seconds)

        rightTurn(); // run the right turn function
        delay(2000); // wait 2 seconds (turn for 2 seconds)
    }
}
