#include <Wire.h>  
#include <LiquidCrystal_I2C.h>  

#define trigger 5  
#define echo 4     
#define Relay 6   
#define LED1 7    
#define LED2 8     
#define LED3 9     
#define LED4 10   
#define LED5 11   

float time = 0, distance = 0;  // Variables to store time and calculated distance

LiquidCrystal_I2C lcd(0x27, 16, 2);  

unsigned long previousMillis = 0;  // Variable for storing the previous time
const long interval = 5000;  // Time interval (5 seconds) for alternating the display
bool displaySurnames = false;  // Boolean to track which message is displayed

void setup() {
  Serial.begin(9600);  

  pinMode(trigger, OUTPUT);  
  pinMode(echo, INPUT);      
  pinMode(Relay, OUTPUT);    

  pinMode(LED1, OUTPUT);  
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  lcd.begin(16, 2);  
  lcd.backlight();   

  lcd.clear();  
  lcd.setCursor(3, 0);  
  lcd.print("Automatic");  
  lcd.setCursor(0, 1);  
  lcd.print("Water Dispenser");  

  digitalWrite(LED1, HIGH);  
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);

  previousMillis = millis();  // Store the current time
  delay(2000);  
}

void loop() {
  measure_distance(); 

  if (distance < 5) {  // If the distance is less than 5 cm
    digitalWrite(Relay, HIGH);  // Turn on the relay
  } else {
    digitalWrite(Relay, LOW);  // Otherwise, turn off the relay
  }

  unsigned long currentMillis = millis(); 

  if (currentMillis - previousMillis >= interval) {  // If 5 seconds have passed
    previousMillis = currentMillis;  // Update the time

    if (displaySurnames) {
      lcd.clear();  
      lcd.setCursor(3, 0);  
      lcd.print("Automatic");  
      lcd.setCursor(0, 1);  
      lcd.print("Water Dispenser");  
    } else {
      lcd.clear();  
      lcd.setCursor(5, 0);  
      lcd.print("Silla");  
      lcd.setCursor(0, 1); 
      lcd.print("Santiago&Gaite");  
    }
    displaySurnames = !displaySurnames; // Flips the value of displaySurnames (true to false or false to true)

  }

  delay(500); 
}

void measure_distance() {
  digitalWrite(trigger, LOW);  // Send a LOW pulse to the trigger pin
  delayMicroseconds(2);  // 
  digitalWrite(trigger, HIGH);  // Send a HIGH pulse to trigger the sensor
  delayMicroseconds(10);  // 
  digitalWrite(trigger, LOW);  // Set trigger pin LOW again
  delayMicroseconds(2);  // 
  time = pulseIn(echo, HIGH);  // Measure the time the echo pin is HIGH

  distance = time * 200 / 20000;  // Calculate the distance in cm between ultrasonic sensor and object
}
