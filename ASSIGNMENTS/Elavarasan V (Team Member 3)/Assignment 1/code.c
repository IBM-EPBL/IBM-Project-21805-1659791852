#include <Servo.h>
int sensorState = 0;
int temp = A0;
int greenLed = 3;
int redLed = 4;
int fan = 7;
int thresholdValue = 0;
int celsius = 0;
int fahrenheit = 0;
int echoPin = 12;
int trigPin = 11;
int servoPin = 10;
int duration; //micro second
float d_cm;
int pos01=0;
int pos02 = 100;
Servo myServo;

// Functions for various work
void greenLightOn(){
	digitalWrite(greenLed, HIGH);
}
void greenLightOff(){
	digitalWrite(greenLed, LOW);
}
void redLightOn(){
	digitalWrite(redLed, HIGH);
}
void redLightOff(){
	digitalWrite(redLed, LOW);
}
void fanOn(){
	digitalWrite(fan, HIGH);
}
void fanOff(){
	digitalWrite(fan, LOW);
}


void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(temp, INPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  myServo.attach(servoPin);
  myServo.write(pos01);
  
  Serial.begin(9600); 
}


void loop()
{
 // read the state of the sensor/digital input
  sensorState = digitalRead(2);
  // check if sensor pin is HIGH. if it is, set the
  // LED on.
  if (sensorState == HIGH) {
    digitalWrite(13, HIGH);
    Serial.println("Sensor activated!");
  } else {
    digitalWrite(13, LOW);
  }
  delay(10);// Delay a little bit to improve simulation performance
  
  // Temperature calculation
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  fahrenheit = ((celsius * 9) / 5 + 32);
  
  Serial.print(celsius);
  Serial.print(" C : ");
  Serial.print(fahrenheit);
  Serial.println(" F");
  
  if( celsius<= 30){
    greenLightOn();
    redLightOff();
    fanOff();
    
    //Serial.println("green light on");
  }
  else if(celsius >= 31 && celsius <= 40){
    greenLightOff();
    fanOff();
    redLightOn();
    //Serial.println("red light on");
  }
  else if(celsius > 40){
    redLightOn();
    fanOn();
    greenLightOff();
    
    //Serial.println("Red Light On | Fan on");
  }
  else{
  	Serial.println("Temperature is Normal");
  }
  delay(1000);
  
  // generate pusle trigger
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  // receive 
  duration = pulseIn(echoPin,HIGH);
  d_cm = duration * 0.034/2.;
  //servo
  if(d_cm>=11 & d_cm<=14){
    for (int i=0;i<=pos02; i+=10){
      myServo.write(i);
      delay(15);
    }
    delay(400);
    myServo.write(pos01);
    delay(1000);
  }
  //print
  Serial.print("Distance:");
  Serial.print(d_cm);
  Serial.println("cm");
}