#include<Arduino.h>
#include<stdint.h>
#include<Wire.h>
#include<switch.h>
#include<controller.h>
#include<mpu6050.h>
#include"MadgwickAHRS.h"
//#define DEBUG // Srial.printを有効にする時

enum Switch
{
    WAIT, 
    WAY,
//    ACT1,
//    WAYBACK,
//    ACT2,
    MANUAL
};

Btd btd;
Madgwick filter;
int state;
double yaw;
std::vector<double>PX1;
std::vector<double>PY1;
int l;
double init_x,init_y,init_v;
int px1[10]={1,2,3,4,5,6,7,8,9,19};
int py1[10]={1,2,3,4,5,6,7,8,9,19};

int mt1=0;
int mt2=0;
int mt3=0;
void setup() {
    Wire.begin();
    mySerial.begin(2400);
    mpu6050_init();
    filter.begin(100);
    Serial.begin(9600);
    /*
    state=Switch::MANUAL;
    
    for(int i=0;i<10;i++){
        PX1.push_back(px1[i]);
        PY1.push_back(py1[i]);
    }
    */

    Wire.beginTransmission(MD1ADDR);
    Wire.write(0);
    Wire.endTransmission();
    
    Wire.beginTransmission(MD2ADDR);
    Wire.write(0);
    Wire.endTransmission();

    Wire.beginTransmission(MD3ADDR);
    Wire.write(0);
    Wire.endTransmission();

    Wire.beginTransmission(MD4ADDR);
    Wire.write(0);
    Wire.endTransmission();
    
    Wire.beginTransmission(MD5ADDR);
    Wire.write(0);
    Wire.endTransmission();
    
   
    Wire.beginTransmission(MD6ADDR);
    Wire.write(0);
    Wire.endTransmission();

    Wire.beginTransmission(MD7ADDR);
    Wire.write(0);
    Wire.endTransmission();

}

void loop() {


    btd.Task(); 

    int x = (btd.Left_x - 64) * 4;
    int y = -1 * (btd.Left_y - 64) * 4;
    int z=0; 

    mt1=-x*cos(yaw)-y*sin(yaw)+l*z;
    mt2=x*(M_PI/2+yaw)-y*((sqrt(3)*M_PI/2)-yaw)+l*z;
    mt3=x*(M_PI/2+yaw)+y*((sqrt(3)*M_PI/2)-yaw)+l*z;

    if(btd.getButtonPress("UP")){

        Wire.beginTransmission(MD4ADDR);
        Wire.write(100);
        Wire.endTransmission();

        Wire.beginTransmission(MD5ADDR);
        Wire.write(100);
        Wire.endTransmission();

        Wire.beginTransmission(MD7ADDR);
        Wire.write(100);
        Wire.endTransmission();
        
    }
    else if(btd.getButtonPress("DOWN")){
        
        Wire.beginTransmission(MD4ADDR);
        Wire.write(-100);
        Wire.endTransmission();

        Wire.beginTransmission(MD5ADDR);
        Wire.write(-100);
        Wire.endTransmission();

        Wire.beginTransmission(MD7ADDR);
        Wire.write(-100);
        Wire.endTransmission();
        
    }

    else if(btd.getButtonPress("RIGHT")){
        Wire.beginTransmission(MD6ADDR);
        Wire.write(100);
        Wire.endTransmission();

    }
    else if(btd.getButtonPress("LEFT")){
        Wire.beginTransmission(MD6ADDR);
        Wire.write(-100);
        Wire.endTransmission();
    }

    else if(btd.getButtonPress("CROSS")){
        Wire.beginTransmission(MD7ADDR);
        Wire.write(-100);
        Wire.endTransmission();
    }

    else{ 
        Wire.beginTransmission(MD4ADDR);
        Wire.write(0);
        Wire.endTransmission();

        Wire.beginTransmission(MD5ADDR);
        Wire.write(0);
        Wire.endTransmission();
    
        Wire.beginTransmission(MD6ADDR);
        Wire.write(0);
        Wire.endTransmission();

        Wire.beginTransmission(MD7ADDR);
        Wire.write(0);
        Wire.endTransmission();
    } 

    

    
    //3-1003 1013
    //2-1029 1000
    //1-252 256
    
   if(mt1>0)mt1=map(mt1,0,256,0,126); 
   if(mt1<0)mt1=map(mt1,-252,0,-126,0); 
   if(mt2>0)mt2=map(mt2,0,1000,0,126);
   if(mt2<0)mt2=map(mt2,-1029,0,-126,0);
   if(mt3>0)mt3=map(mt3,0,1013,0,126);
   if(mt3<0)mt3=map(mt3,-1003,0,-126,0);
    
    Serial.println(mt3);
    Serial.println(mt1);
    Serial.println(mt2);
   
    if(mt1<0){
        uint8_t num; 
        num=~abs(mt1);
        mt1=num+0b1;
     }
    if(mt2<0){
        uint8_t num; 
        num=~abs(mt2);
        mt2=num+0b1;
    } 
    if(mt3<0){
        uint8_t num;
        num=abs(mt3);
        mt3=num+0b1;
    }
    
    Wire.beginTransmission(MD1ADDR);
    Wire.write(mt1);
    Wire.endTransmission();
    
    Wire.beginTransmission(MD2ADDR);
    Wire.write(mt2);
    Wire.endTransmission();

    Wire.beginTransmission(MD3ADDR);
    Wire.write(mt3);
    Wire.endTransmission();
/*
    Wire.beginTransmission(MD4ADDR);
    Wire.write(0);
    Wire.endTransmission();
    
    Wire.beginTransmission(MD5ADDR);
    Wire.write(0);
    Wire.endTransmission();
    
   
    Wire.beginTransmission(MD6ADDR);
    Wire.write(100);
    Wire.endTransmission();

    Wire.beginTransmission(MD7ADDR);
    Wire.write(100);
    Wire.endTransmission();
*/
/*
    switch(state){
        case Switch::WAIT :
            Wire.beginTransmission(MD1ADDR);
            Wire.write(0);
            Wire.endTransmission();
        
            Wire.beginTransmission(MD2ADDR);
            Wire.write(0);
            Wire.endTransmission();

            Wire.beginTransmission(MD3ADDR);
            Wire.write(0);
            Wire.endTransmission();

            if(btd.getButtonPress("START")){
                state=Switch::WAY;
            }
            else if(btd.getButtonPress("UP")){
                state=Switch::MANUAL;
            }
            break;

        case Switch::WAY:{
            
            Auto* au=new Auto;
            au->make_root(PX1,PY1);
            state=au->run(init_x,init_y,init_v);
            delete au;
          } 
            break;
        
        case Switch::MANUAL:{
         
            Serial.print("manual");
            //mpu6050_getdata(); 
            //filter.updateIMU(xGyro,yGyro,zGyro,xAccl,yAccl,zAccl);
            yaw=0;//filter.getYaw();


            int x = (btd.Left_x - 64) * 4;
            int y = -1 * (btd.Left_y - 64) * 4;
            int z=0; 

            int mt1=3;//-x*cos(yaw)-y*sin(yaw)+l*z;
            int mt2=2;//x*(M_PI/2+yaw)-y*((sqrt(3)*M_PI/2)-yaw)+l*z;
            int mt3=1;//x*(M_PI/2+yaw)+y*((sqrt(3)*M_PI/2)-yaw)+l*z;

            if(btd.getButtonPress("UP")){
                Wire.beginTransmission(MD4ADDR);
                Wire.write(100);
                Wire.endTransmission();

                Wire.beginTransmission(MD5ADDR);
                Wire.write(100);
                Wire.endTransmission();
            }
            else if(btd.getButtonPress("DOWN")){
                
                Wire.beginTransmission(MD4ADDR);
                Wire.write(-100);
                Wire.endTransmission();

                Wire.beginTransmission(MD5ADDR);
                Wire.write(-100);
                Wire.endTransmission();
            }

            else if(btd.getButtonPress("RIGHT")){
                Wire.beginTransmission(MD6ADDR);
                Wire.write(100);
                Wire.endTransmission();
            }
            else if(btd.getButtonPress("LEFT")){
                Wire.beginTransmission(MD6ADDR);
                Wire.write(-100);
                Wire.endTransmission();
            }

           else{ 
                Wire.beginTransmission(MD4ADDR);
                Wire.write(0);
                Wire.endTransmission();

                Wire.beginTransmission(MD5ADDR);
                Wire.write(0);
                Wire.endTransmission();
           
                Wire.beginTransmission(MD6ADDR);
                Wire.write(0);
                Wire.endTransmission();
            } 

            if(mt1>=127)mt1=126;
            if(mt2>=127)mt2=126;
            if(mt3>=127)mt3=126;

            if(mt1<=-127)mt1=-126;
            if(mt2<=-127)mt2=-126;
            if(mt3<=-127)mt3=-126;
            
            
            if(mt1<0){
                uint8_t num; 
                num=~abs(mt1);
                mt1=num+0b1;
             }
            if(mt2<0){
                uint8_t num; 
                num=~abs(mt2);
                mt2=num+0b1;
            } 
            if(mt3<0){
                uint8_t num;
                num=abs(mt3);
                mt3=num+0b1;
            }


            Wire.beginTransmission(MD1ADDR);
            Wire.write(100);
            Wire.endTransmission();
    
            Wire.beginTransmission(MD2ADDR);
            Wire.write(100);
            Wire.endTransmission();

            Wire.beginTransmission(MD3ADDR);
            Wire.write(100);
            Wire.endTransmission();

            Wire.beginTransmission(MD4ADDR);
            Wire.write(100);
            Wire.endTransmission();
            
           
           } 
            break;
        default:
            break;
            
    } 
    */


    

}
