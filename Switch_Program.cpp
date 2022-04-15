const int sw1 = 2;
const int LED = 7;

byte Sw_Count = 0;
boolean Sw_State = 0;

void setup(){
    pinMode(sw1,INPUT_PULLUP);
    pinMode(LED,OUTPUT);
}

void loop(){

if(digitalRead(sw1) == LOW){
    
    if((Sw_Count < 5 ) ){
      Sw_Count++;
      if(Sw_Count >=5){
        Sw_State = !Sw_State;
      }
    }
} else Sw_Count = 0;
    
    
digitalWrite(LED,Sw_State);
}