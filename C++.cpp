C++





//Temperature Sensor
int pinTemp = A1; //assign analog 1 as the temp sensor 

//define the maximum cutoff temp for shutdown
int maxTemp = (pinTemp > 75);


// Setup Code
void setup()
{
    Serial.begin(9600);
}



// Main Code
void loop()


{

}

 // function commands

void tooHot()
for (int i = pinTemp; i <= maxTemp; i++)
    digitalWrite(i, HIGH);

    if (i == maxTemp)
    {
      digitalWrite(endLED, LOW);
    }
    else
    {
      digitalWrite(i - 1, LOW);
    delay(delayTime);
  }

  //stop the car
void killSwitch()
{
    analogWrite(rightEn, 0); // enable right motor
    analogWrite(leftEn, 0);  // enable left motor
}


////////////////////////////////////////////

/* //Working Temp Reading

// C++ code
//

//Temperature Sensor
int pinTemp = A1; //assign analog 1 as the temp sensor 


// Setup Code
void setup()
{
    Serial.begin(9600); //Start the serial monitor
}

// Main Code
void loop()
{
readTemp();
}  


//Function to read the temperature
void readTemp()
 {
  int temp = analogRead(pinTemp);    //Read the analog pin
  temp = temp * 0.48828125;   // convert output (mv) to readable celcius
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("C");  //print the temperature status
  delay(1000);  
} */

float temp;

int tempPin = A0; //arduino pin used for temperature sensor

int tempMin = 25; // the temperature to start the buzzer

int tempMax = 70;

int fan = 6; // the pin where fan is connected

int fanSpeed = 0;

void setup() {

pinMode(fan, OUTPUT);

pinMode(tempPin, INPUT);

Serial.begin(9600);

}

void loop() 
{

temp = analogRead(tempPin);

temp = (temp *5.0*100.0)/1024.0; //calculate the temperature in Celsius

Serial.println(temp);

delay(1000); // delay in between reads for stability


if(temp < tempMin) 
{ // if temp is lower than minimum temp

fanSpeed = 0; // fan is not spinning

digitalWrite(fan, LOW);

}

if((temp >= tempMin) && (temp <= tempMax)) //if temperature is higher than the minimum range

{

fanSpeed = map(temp, tempMin, tempMax, 32, 255); // the actual speed of fan

analogWrite(fan, fanSpeed); // spin the fan at the fanSpeed speed

}

}