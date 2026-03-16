#include <ControlMotor.h>
#include <Ultrasonic.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>


ControlMotor control(2, 3, 4, 7, 5, 6); 
Ultrasonic sensor(9, 8, 30000); 

SoftwareSerial mySoftwareSerial(11, 10); 
DFRobotDFPlayerMini myDFPlayer;


int mesurement_speed = 5;
long int distance = 0;
int random_value = 0;

void setup() 
{ 
  Serial.begin(9600); 
  mySoftwareSerial.begin(9600); 

  Serial.println(F("Initializare DFPlayer..."));

  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Eroare: Verifica conexiunile sau cardul SD!"));
  } else {
    Serial.println(F("DFPlayer online."));
  }
  
  myDFPlayer.volume(25); 
  
  
  myDFPlayer.play(3);
  delay(1000);
} 

void loop() 
{ 
  
  distance = sensor.Ranging(CM); 
  delay(mesurement_speed); 

  Serial.print("Distanta: ");
  Serial.println(distance);

  
  random_value = random(2);

  
  if (distance > 0 && distance < 10) {
      
      Serial.println("CRITIC (<10cm)! Redare 001.mp3");
      
      control.Motor(0, 1); 
  
      myDFPlayer.play(1); 
      
     
      delay(2000); 

      
      manevraEvitare();
  }
  

  else if (distance > 10 && distance < 15) {
      
      Serial.println("AVERTISMENT (<15cm)! Redare 002.mp3");
      
      
      control.Motor(0, 1);
      
     
      myDFPlayer.play(2);
      
      
      delay(2000);

      
      manevraEvitare();
  }
  
  
  else {
      
      control.Motor(150, 1); 
  }
}


void manevraEvitare() {
    if(random_value == 0) {
       Serial.println("Viraj Dreapta");
       control.Motor(170, 100);
       delay(500);               
    } 
    else {
       Serial.println("Viraj Stanga");
       control.Motor(170, -100);   
       delay(500);               
    }
    
    control.Motor(0, 1);
    delay(100);
}