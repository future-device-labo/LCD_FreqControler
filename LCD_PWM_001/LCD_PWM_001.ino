#include <LiquidCrystal.h>

#define Sw1 2
#define Sw2 4
#define RS 13
#define E 12
#define D4 14
#define D5 15
#define D6 16
#define D7 17

#define PWM1 9
#define PWM2 10

LiquidCrystal lcd(RS,E,D4,D5,D6,D7);

byte Sw1_State = 0x01;
byte Sw1_ChataState = 0x00;

byte Sw2_State = 0x01;
byte Sw2_ChataState = 0x00;

float freq = 120.0;
float duty = 50.0;

float freq_min = 50;
float freq_max = 1000;


void setup() {


  pinMode(Sw1,INPUT_PULLUP);
  pinMode(Sw2,INPUT_PULLUP);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  TCCR1A = 0b10100011;
  TCCR1B = 0b00011001;
  OCR1A = (16000 / freq); 
  OCR1B = OCR1A*(duty/100);
  
  lcd.begin(20,4);
  lcd.clear();
  /*
  lcd.setCursor(2, 0);
  lcd.print("Pulse Generator");
  //lcd.clear();
  lcd.setCursor(3, 2);
  lcd.print("v0.01");
  delay(5000);
  lcd.clear();
  delay(2000);
  */
  lcd.print("<TIM1>");
  lcd.setCursor(0, 2);
  lcd.print("f=");
  lcd.setCursor(2, 2);
  lcd.print(freq);
  lcd.setCursor(8, 2);
  lcd.print("kHz");
  lcd.setCursor(12, 2);
  lcd.print("dt=");
  lcd.setCursor(15, 2);
  lcd.print(duty);
  lcd.setCursor(0, 3);
  lcd.print("OCR1A=");
  lcd.setCursor(6, 3);
  lcd.print(OCR1A);
  //lcd.setCursor(4, 2);
  //lcd.print(">");
}

  //CH1(4,2),CH2(4,4)
  //CH3(12,2,I2C(12,4)

void loop() {
  if( !digitalRead(Sw1) ){
    if(Sw1_ChataState < 3){
      Sw1_ChataState++;
        if(Sw1_ChataState>=3){
          freq+=0.5;
          if(freq>=freq_max) freq = freq_max;
          lcd.setCursor(2, 2);
          lcd.print(freq);
          OCR1A = (16000 / freq); 
          OCR1B = OCR1A*(duty/100);
          OCRnx_Crear();
          lcd.setCursor(6, 3);
          lcd.print(OCR1A);
          
        }
    }     
  }
  else Sw1_ChataState = 0 ;

  if( !digitalRead(Sw2) ){
    if(Sw2_ChataState < 3){
      Sw2_ChataState++;
        if(Sw2_ChataState>=3){
          freq-=0.5;
          if(freq<=freq_min) freq = freq_min;
          lcd.setCursor(2, 2);
          lcd.print(freq);
          OCR1A = (16000 / freq); 
          OCR1B = OCR1A*(duty/100);
          OCRnx_Crear();
          lcd.setCursor(6, 3);
          lcd.print(OCR1A);
        }
    }     
  }
  else Sw2_ChataState = 0 ;
  
  if(Sw1_State>4) Sw1_State=1;
}

//SW押されたら

void SelectMark_Crear(void){
  lcd.setCursor(4, 2);
  lcd.print(" ");
  lcd.setCursor(4, 4);
  lcd.print(" ");
  lcd.setCursor(12, 2);
  lcd.print(" ");
  lcd.setCursor(12, 4);
  lcd.print(" ");
}

void OCRnx_Crear(void){
  lcd.setCursor(6, 3);
  lcd.print("   ");

}
