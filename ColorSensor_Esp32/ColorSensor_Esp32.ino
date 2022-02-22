#include <analogWrite.h>

//Initialise Pin for LDR sensor (photoresistor)
const int ldrPin = 4;

//Initialise Pins for RGB LED
const int rPin = 19;
const int gPin = 18;
const int bPin = 5;


//RGB callibration variables for BLACK (min)
int minRcal;
int minGcal;
int minBcal;
//RGB callibration variable for WHITE (max)
int maxRcal;
int maxGcal;
int maxBcal;

void setup() {

  //Serial Init
  Serial.begin(9600);
  Serial.println("Calibration for BLACK initialising in 3 secs");
  delay(3000);

  //set input & output pins
  pinMode(ldrPin,INPUT);
  pinMode(rPin,OUTPUT);
  pinMode(gPin,OUTPUT);
  pinMode(bPin,OUTPUT);
  pinMode(2, OUTPUT); //built-in LED for ESP32

  Serial.println("Calibrating Black Value..");
  digitalWrite(2, HIGH);
  
  setColor(255,0,0); //LED to Red
  delay(100);
  minRcal = analogRead(ldrPin);

  setColor(0,255,0); //LED to Green
  delay(100);
  minGcal = analogRead(ldrPin);

  setColor(0,0,255); //LED to Blue
  delay(100);
  minBcal = analogRead(ldrPin);  
  
  digitalWrite(2, LOW); //END OF BLACK Calibration

  Serial.println("Calibration for WHITE Initialising in 3 Secs");
  delay(3000);

  Serial.println("Calibrating White Value..");
  digitalWrite(2, HIGH);

  setColor(255,0,0); //LED to Red
  delay(100);
  maxRcal = analogRead(ldrPin);

  setColor(0,255,0); //LED to Green
  delay(100);
  maxGcal = analogRead(ldrPin);

  setColor(0,0,255); //LED to Blue
  delay(100);
  maxBcal = analogRead(ldrPin);  
  
  digitalWrite(2, LOW); //END OF WHITE Calibration

  Serial.println("Calibration Complete!!!");
  setColor(0,0,0);
  delay(1000);
}

int refreshRate = 100; //in milliseconds
void loop() {
  // put your main code here, to run repeatedly:
  
  setColor(255,0,0); //LED to Red
  delay(refreshRate);
  int redVal = constrain(map(analogRead(ldrPin), minRcal , maxRcal, 0, 255),0,255);

  setColor(0,255,0); //LED to Green
  delay(refreshRate);
  int greenVal = constrain(map(analogRead(ldrPin), minGcal , maxGcal, 0, 255),0,255);

  setColor(0,0,255); //LED to Blue
  delay(refreshRate);
  int blueVal = constrain(map(analogRead(ldrPin), minBcal , maxBcal, 0, 255),0,255); 

  Serial.println(String(redVal) + "," + String(greenVal) + ", " + String(blueVal)); // to be send over to Processing
  delay(refreshRate);
}

//set RGB LED to a certain color
void setColor(int red, int green, int blue){
  analogWrite(rPin,red);
  analogWrite(gPin,green);
  analogWrite(bPin,blue);
  }
