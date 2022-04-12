#include<Arduino.h>
#include<Wire.h>



void setup(){
   Wire.begin(10);
   Wire.onReceive(event);
   Serial.begin(9600);
}

void loop(){
    delay(100);
}
void event(int a){
        int c=Wire.read();       
        Serial.print(c);
}
