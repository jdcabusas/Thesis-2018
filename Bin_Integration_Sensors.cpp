#define trigPin1 3 //orange
#define echoPin1 2 //yellow
#define trigPin2 5 //white
#define echoPin2 4 //black
#define trigPin3 10 //brown
#define echoPin3 9 //red
#include <SoftwareSerial.h>
SoftwareSerial SIM900(7,8);

int GasSensor = A0; 
int GasReading;
int duration, distance, RightSensor, FrontSensor, LeftSensor, average, timecounter;


void setup()
{
  SIM900.begin(19200);
  Serial.begin (19200);
  
  
  pinMode(GasSensor, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  Serial.println("Starting");
  delay(10000);
}

void  loop() {
  

  SonarSensor(trigPin1, echoPin1);
  LeftSensor = distance;
  delay(1000);
  SonarSensor(trigPin2, echoPin2);
  FrontSensor = distance;
  delay(1000);
  SonarSensor(trigPin3, echoPin3);
  RightSensor = distance;
  delay(1000);
  GasReading = analogRead(GasSensor);
  
  average = (LeftSensor+RightSensor+FrontSensor)/3;
  
  Serial.print("Gas Reading: ");
  Serial.println(GasReading);
  Serial.print(LeftSensor);
  Serial.print(" - ");
  Serial.print(FrontSensor);
  Serial.print(" - ");
  Serial.println(RightSensor);
  Serial.println(average);
  
  if((average >= 49) && (average <= 63)){
    Serial.println(" EMPTY ");
    //SIM900.begin(19200);
    sendSMS_Empty();
    //SIM900.close;
    }
  else if((average >= 38) && (average < 49)){
    Serial.println(" SEMI-FULL ");    
    sendSMS_SFull();
    
    }
  else if(average < 37){
    Serial.println(" FULL ");
    sendSMS_Full();
    }

    /*if(GasReading > 100){
      Serial.print("Gas Reading EMERGENCY");
    Serial.println(GasReading);
      delay(10000);
       if(GasReading > 100){
      emergencyText();
      }
    }*/
    
    
   //delay(2000);

    LeftSensor = 0;
    RightSensor = 0;
    FrontSensor = 0;

   

   
    
}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = duration/58;


}

void sendSMS_Full(){
  SIM900.print("AT+CMGF=1\r"); // AT command to SMS mode to text
  delay(100);
  SIM900.println("AT + CMGS = \"+639235288800\""); // Change this to your desired recipient mobile number. (international format)
  delay(100);
  SIM900.println("Full."); // Message to send  
  SIM900.print("Gas Reading: ");
  SIM900.println(GasReading);
  SIM900.print(LeftSensor);
  SIM900.print(" - ");
  SIM900.print(FrontSensor);
  SIM900.print(" - ");
  SIM900.println(RightSensor);
  SIM900.print("Average: ");
  SIM900.println(average);// Message to send
  delay(100);
  SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
  delay(100);
  SIM900.println();
  delay(5000); // give module time to send SMS
}

void sendSMS_SFull(){
  SIM900.print("AT+CMGF=1\r"); // AT command to SMS mode to text
  delay(100);
  SIM900.println("AT + CMGS = \"+639235288800\""); // Change this to your desired recipient mobile number. (international format)
  delay(100);
  SIM900.println("Semi-Full.");
  SIM900.print("Gas Reading: ");
  SIM900.println(GasReading);
  SIM900.print(LeftSensor);
  SIM900.print(" - ");
  SIM900.print(FrontSensor);
  SIM900.print(" - ");
  SIM900.println(RightSensor);
  SIM900.println(average);// Message to send;
  delay(100);
  SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
  delay(100);
  SIM900.println();
  delay(5000); // give module time to send SMS
}

void sendSMS_Empty(){
  SIM900.print("AT+CMGF=1\r"); // AT command to SMS mode to text
  delay(100);
  SIM900.println("AT + CMGS = \"+639235288800\""); // Change this to your desired recipient mobile number. (international format)
  delay(100);
  SIM900.println("Empty.");
  SIM900.print("Gas Reading: ");
  SIM900.println(GasReading);
  SIM900.print(LeftSensor);
  SIM900.print(" - ");
  SIM900.print(FrontSensor);
  SIM900.print(" - ");
  SIM900.println(RightSensor);
  SIM900.println(average);// Message to send
  delay(100);
  SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
  delay(100);
  SIM900.println();
  delay(5000); // give module time to send SMS
}

void emergencyText(){
  SIM900.print("AT+CMGF=1\r"); // AT command to SMS mode to text
  delay(100);
  SIM900.println("AT + CMGS = \"+639235288800\""); // Change this to your desired recipient mobile number. (international format)
  delay(100);
  
  SIM900.println("GAS LEAK DETECTED IN BIN");
  SIM900.println(GasReading );

  delay(100);
  SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
  delay(100);
  SIM900.println();
  delay(5000); // give module time to send SMS
}


