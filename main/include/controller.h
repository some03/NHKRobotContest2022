#ifndef BTD_H
#define BTD_H
#include<HardwareSerial.h>
#include<Arduino.h>
//#include<string>
#define MYRX PA10
#define MYTX PA9
HardwareSerial mySerial(MYRX,MYTX);
class Btd{
    public:
        Btd();
        int i;
        unsigned char c[8];
        unsigned long chksum;
        int Left_x;
        int Left_y;
        int Right_x;         
        int Right_y;
        void Task();
        bool getButtonPress(String name);
        bool Check(int c,int num);
        bool Check_SS(int c,int num0,int num1);
};
Btd::Btd(){
    c[0]=0x80;
}
bool Btd::Check(int c,int num){
    if((c&num)==num)return true;
    else return false;
}
bool Btd::Check_SS(int c,int num0,int num1){
    if((c&num0)==num0 && (c&num1)==num1)return true;
    else return false;
    Serial.println("b"); 
}
bool Btd::getButtonPress(String name){
    bool rep;
     Serial.println(c[2]);
     //delay(50);
     //if(c[2]==3)Serial.println(name);
    if(name=="CROSS") rep=Check(c[2],0x20);
    else if(name=="CIRCLE") rep=Check(c[2],0x40);
    else if(name=="TRIANGLE") rep=Check(c[2],0x10);
    else if(name=="SQUARE") rep=Check(c[1],0x01);
    else if(name=="START") rep=Check(c[2],0x03);
    else if(name=="DOWN") rep=Check(c[2],0x02);
    else if(name=="RIGHT") rep=Check(c[2],0x04);
    else if(name=="LEFT") rep=Check(c[2],0x08);
    else if(name=="L1") rep=Check(c[1],0x02);
    else if(name=="L2") rep=Check(c[1],0x04);
    else if(name=="R1") rep=Check(c[1],0x08);
    else if(name=="R2") rep=Check(c[1],0x10);
    else if(name=="UP")rep=Check(c[2],0x01);
    else if(name=="SELECT") rep=Check(c[2],0x0c);
    else rep=false; 
    return rep;
}
void Btd::Task(){
    if(mySerial.available()>=8){
        if(mySerial.read()==0x80){
            for(chksum=c[0],i=1;i<8;i++){
                c[i]=mySerial.read();
                if(i<7)chksum+=c[i];
            }
            //if(c[7]!=(chksum & 0x7F))throw "check sum EROOR";
            String leftstickx=String(c[3],DEC);
            String leftsticky=String(c[4],DEC);
            String rightstickx=String(c[5],DEC);
            String rightsticky=String(c[6],DEC);
            Left_x=leftstickx.toInt();
            Left_y=leftsticky.toInt();
            Right_x=rightsticky.toInt();
            Right_y=rightsticky.toInt();
        }
    }
}
#endif

