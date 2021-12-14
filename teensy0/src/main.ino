#include<Arduino.h>
#include"MadgwickAHRS.h"
#include<mpu6050.h>


/*
 3 ↗　　↘ 0

 2 ↖　　↙ 1
   
*/


Madgwick filter;
int vx,vy;
int theta;
int m[4];
double roll,pitch,yaw;

void setup(){
    Wire.begin();
    Serial.begin(115200);
    filter.begin(100);
    mpu6050_init();
    delay(300);
}

void loop(){

    mpu6050_getdata();    
    filter.updateIMU(xGyro,yGyro,zGyro,xAccl,yAccl,zAccl); 
    roll=filter.getRoll();
    pitch=filter.getPitch();
    yaw=filter.getYaw();

    Serial.println(yaw);
    Serial.print("g");
    Serial.println(zGyro);
    delay(100);
    
    m[0]=v*cos(M_PI/2+theta)-v*sin(M_PI/2+theta);
    m[1]=-v*cos(M_PI/2-theta)-v*sin(M_PI/2-theta);
    m[2]=-v*cos(M_PI/2+theta)+v*sin(M_PI/2+theta);
    m[3]=v*cos(M_PI/2-theta)+v*sin(M_PI/2-theta);
}

