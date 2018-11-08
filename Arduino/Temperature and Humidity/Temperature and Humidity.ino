#include <Arduino.h>
#include<dht.h>
#include <LiquidCrystal.h>

dht DHT;

// if you require to change the pin number, Edit the pin with your arduino pin.
#define DHT11_PIN 6

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() 
{

Serial.begin(9600);

Serial.println("welcome to TechPonder Humidity and temperature Detector"); 

// set up the LCD's number of columns and rows:
lcd.begin(16, 2);

pinMode(5, OUTPUT);
digitalWrite(5, HIGH);

pinMode(7, OUTPUT);
digitalWrite(7, LOW);
}

void loop() { // READ DATA

int chk = DHT.read11(DHT11_PIN);

Serial.println(" Humidity " );

Serial.println(DHT.humidity, 1);

Serial.println(" Temparature ");

Serial.println(DHT.temperature, 1);

lcd.setCursor(0, 1);
lcd.print("Humidity:");
lcd.print(DHT.humidity);

delay(2000);

}
