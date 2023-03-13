#include <LiquidCrystal_I2C.h>
#include "TimerOne.h"
LiquidCrystal_I2C lcd(0x27,16,2);

#define PI 3.1415926535897932384626433832795

volatile int counter=0;
volatile double opseg;
volatile int brzina;

volatile int brzinaOld;
volatile bool flag=false;
double time = 0;
double oldtime;

void setup() {
  pinMode(2,INPUT_PULLUP);
  double r=0.25;
  opseg=2*r*PI;
  attachInterrupt(digitalPinToInterrupt(2),broji,RISING);
  lcd.init();
  lcd.backlight();
}

void loop() {
  if(flag){
    lcd.clear();
    flag=false;
  }

  if(counter>5){
    brzinaOld = brzina;
    oldtime=time;
    time=millis()/1000.0;      
    brzina = (opseg*counter)/(time-oldtime)*3.6;
    counter = 0;      
    
    if(brzina!=brzinaOld){
      brzinaOld=brzina;
      flag=true;
    }
  }

  lcd.setCursor(4, 0);
  lcd.print(brzina);

  lcd.setCursor(8, 0);
  lcd.print("km/h");
}

void broji(){
  counter=counter+1;
}