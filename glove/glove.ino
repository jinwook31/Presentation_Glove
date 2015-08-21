#include <Wire.h>
#include <Time.h>
#include <LiquidCrystal_I2C.h>
#include <BPLib.h>

#define LASER 11 //laser 11
#define BUTTON 6 //laserbutton 6
BPLib BPMod;

LiquidCrystal_I2C lcd(0x27,16,2);
int buttonState = 0;
unsigned int num=0;
//lcd

const int mouseButton = 4;//mouse and lcd button = 4
int val = 0;
int old_val = 0;
int state = 0;

void setup(){
  BPMod.begin(BP_MODE_HID,BP_HID_MOUSE);
  pinMode(LASER,OUTPUT);
  pinMode(BUTTON,INPUT);
  pinMode(mouseButton, INPUT);
  lcd.init();  
  pinMode(8, INPUT_PULLUP); //backbutton = 8;
  setTime(0,0,0,27,2,15);
}

void loop(){
  LEDButtonSwitch();
  Next();
  Back();
  LcdControl();
  digitalClockDisplay();
}

void digitalClockDisplay(){
     lcd.setCursor(0,1);
     lcd.print("TIME ");
     lcd.print(hour());
     printDigits(minute());
     printDigits(second());
     delay(100);
 }
 
void printDigits(int digits){
    lcd.print(":");
    if (digits < 10)
      lcd.print('0');
      lcd.print(digits);
}

void LcdControl() {
  buttonState = digitalRead(mouseButton);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(num);
  if (buttonState==LOW){ 
    lcd.setCursor(0,0);
    lcd.clear();
    num++;
    lcd.print(num);
    delay(100);
  }
}
void Back(){
  while (digitalRead(8) == LOW) {
      BPMod.mouseWheel(-1);
      lcd.setCursor(0,0);
      lcd.clear();
      if(num != 0){
      num--;
    }
    lcd.print(num);
    delay(130);
  }
}

void Next(){
  int clickState = digitalRead(mouseButton);
  if(clickState == LOW){
    BPMod.mouseWheel(1);
  }
  delay(10);
}

void LEDButtonSwitch(){
  val = digitalRead(BUTTON);
  if((val==HIGH) && (old_val == LOW)){
    state = 1 - state;
    delay(10);
  }
  old_val = val;
  if(state == 1){
    digitalWrite(LASER,LOW);
   } else {
    digitalWrite(LASER,HIGH);
  }
}
