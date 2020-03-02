// Print battery voltage
// to 16x2 LCD via I2C
// with Voltage Divider (2x 10K resistor)
/*
  Resistors are aligned in series.
  One end goes to Battery - and also to Arduino GND
  The other goes to Battery + and also to Arduino Vin
  The middle (connection between two resistors) goes to Arduino A0
*/
//Edited by Melissa Kerins
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

#define I2C_ADDR    0x27 //Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
#define led_pin 13
//#LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup()
{
  lcd.begin (16,2); //My LCD was 16x2
  //lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  //lcd.setBacklight(HIGH);
  lcd.home (); // go home
  
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
}

void loop()
{
  float voltage = printVolts();
  setBackgroundColour(voltage);
}
 
 float printVolts()
{
  int sensorValue = analogRead(A0); //read the A0 pin value
  float voltage = sensorValue * (5.00 / 1023.00) * 2; //convert the value to a true voltage.
  lcd.setCursor(0,0);
  lcd.print("voltage = ");
  lcd.print(voltage); //print the voltage to LCD
  lcd.print(" V");
  return voltage;
  //if (voltage < 6.50) //set the voltage considered low battery here
  //{
  // digitalWrite(led_pin, HIGH);
  //}
}

void setBackgroundColour(float voltage)
{
  if(voltage < 4.00)
  {
    const int colorR = 255;
    const int colorG = 0;
    const int colorB = 0;
    lcd.setRGB(colorR, colorG, colorB);
  }
  else
  {
    const int colorR = 0;
    const int colorG = 255;
    const int colorB = 0;
    lcd.setRGB(colorR, colorG, colorB);
  }
}
