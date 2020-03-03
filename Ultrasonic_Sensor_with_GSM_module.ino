#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8);

#define trigPin1 3
#define echoPin1 2
#define trigPin2 5
#define echoPin2 4
#define trigPin3 10
#define echoPin3 9

int redPin = 13;
int greenPin = 12;
int bluePin = 11;

int distance, duration, TU_Sensor, MU_Sensor, BU_Sensor;

void setup() {

  //SetUp for GSM Module
  SIM900.begin(19200);
  
  //SetUp for Ultrasonic Sensor
  Serial.begin(19200);
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);

  //SetUp for RGB LED
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  delay(20000); //GSM Module manual power on delay 
}

void loop() {
  
  U_Sensor(trigPin1, echoPin1);
  TU_Sensor = distance;
  U_Sensor(trigPin2, echoPin2);
  MU_Sensor = distance;
  U_Sensor(trigPin3, echoPin3);
  BU_Sensor = distance;

  Serial.print("Ultrasonic Sensor Reading: ");
  Serial.print(TU_Sensor);
  Serial.print(" - ");
  Serial.print(MU_Sensor);
  Serial.print(" - ");
  Serial.println(BU_Sensor);

  if(TU_Sensor >= 85 && MU_Sensor >= 85 && BU_Sensor >= 85){
    setColor(0, 255, 0);
    sendSMS_Empty();
  }
  else if((TU_Sensor >= 30 && TU_Sensor <85) && (MU_Sensor >= 30 && MU_Sensor <85) && (BU_Sensor >= 30 && BU_Sensor <85)){
    setColor(255, 150, 51);
    sendSMS_SFull();
  }
  else if(TU_Sensor < 30 && MU_Sensor < 30 && BU_Sensor < 30){
    setColor(255, 0, 0);
    sendSMS_Full();
  } 
  
  delay(30000);
  delay(30000);
}

void U_Sensor(int trigPin, int echoPin){

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,  LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58;
}

void setColor(int red, int green, int blue){

analogWrite(redPin, red);
analogWrite(greenPin, green);
analogWrite(bluePin, blue);
  
}

void sendSMS_Full(){
  SIM900.print("AT+CMGF=1\r"); // AT command to SMS mode to text
  delay(100);
  SIM900.println("AT + CMGS = \"+639291645540\""); // Change this to your desired recipient mobile number. (international format)
  delay(100);
  SIM900.println("Full."); // Message to send
  delay(100);
  SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
  delay(100);
  SIM900.println();
  delay(5000); // give module time to send SMS
}

void sendSMS_SFull(){
  SIM900.print("AT+CMGF=1\r"); // AT command to SMS mode to text
  delay(100);
  SIM900.println("AT + CMGS = \"+639291645540\""); // Change this to your desired recipient mobile number. (international format)
  delay(100);
  SIM900.println("Semi-Full."); // Message to send
  delay(100);
  SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
  delay(100);
  SIM900.println();
  delay(5000); // give module time to send SMS
}

void sendSMS_Empty(){
  SIM900.print("AT+CMGF=1\r"); // AT command to SMS mode to text
  delay(100);
  SIM900.println("AT + CMGS = \"+639291645540\""); // Change this to your desired recipient mobile number. (international format)
  delay(100);
  SIM900.println("Empty."); // Message to send
  delay(100);
  SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
  delay(100);
  SIM900.println();
  delay(5000); // give module time to send SMS
}

