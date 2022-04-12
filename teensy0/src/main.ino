#include<Arduino.h>
#include"MadgwickAHRS.h"
#include<mpu6050.h>
//#include"controller_convert.h"
#include"controller.h"

/*
 3 ↗　　↘ 0

 2 ↖　　↙ 1
   
*/


Madgwick filter;
Btd btd;
int vx,vy;
int theta=0;
int m[4];
double roll,pitch,yaw;

/*
double angle(double x_, double y_) {
  float deg1;
  float rad = atan2(y_, x_);
  float deg = rad / PI * 180;
  if (deg<0) deg1=deg+360;
  else deg1=deg;
  return deg1;
}

int x = (btd.Left_x - 64) * 4;
int y = -1 * (btd.Left_y - 64) * 4;

if(x>0)x=map(x,0,252,0,255);
else if(x<0)x=map(x,-256,0,-255,0);

if(y>0)y=map(y,0,256,0,255);
else if(y<0)y=map(y,-252,0,-255,0);

int theta_=angle(x,y);
int v=sqrt(pow(x,2),pow(y,2));
convert(v,theta_);
*/
/*
int32_t addr=0,addcode=0,dir=0,rxne=0,rxdata=0;
void i2cset(){
    
    RCC->APB1ENR|=1<<21;
    RCC->AHBENR|=1<<18;//PB6,PB7
    GPIOB->MODER&=~(1<<12);
    GPIOB->MODER|=1<<13;

    GPIOB->MODER&=~(1<<14);
    GPIOB->MODER|=1<<15;

    GPIOB->OSPEEDR|=1<<14;
    GPIOB->OSPEEDR|=1<<15;

    GPIOB->OSPEEDR|=1<<12;
    GPIOB->OSPEEDR|=1<<13;

    //i2c初期化----------------------

    I2C1->CR1&=~1;
    I2C1->CR1&=~(1<<12);
    //i2cタイミングレジスタ------------ 
    I2C1->TIMINGR|=1<<28; 
    I2C1->TIMINGR|=1<<22; 
    I2C1->TIMINGR|=1<<17; 
    I2C1->TIMINGR|=1; 
    I2C1->TIMINGR&=~(1<<1); 
    I2C1->TIMINGR|=1<<2; 
    I2C1->TIMINGR|=1<<3; 
    I2C1->TIMINGR|=1<<8; 
    I2C1->TIMINGR|=1<<9; 
    I2C1->TIMINGR|=1<<10; 
    I2C1->TIMINGR|=1<<11; 
    //--------------------------------- 
    I2C1->CR1|=1;
    //---------------------------------
    //i2cスレーブモード初期化
    I2C1->OAR1&=~(1<<15);
    I2C1->OAR2&=~(1<<15);
    I2C1->OAR1|=1<<1;//スレーブアドレス
    I2C1->OAR1&=~(1<<10);//7bitアドレスモード
    I2C1->OAR1|=(1<<15);
    I2C1->CR1|=1<<19;//同報on
    I2C1->CR1|=1<<2;

    addr=I2C1->ISR&(1<<3);
    while(!addr){
        Serial.println("addr not 1");
    }
    addcode=I2C1->ISR>>17;
    dir=(I2C1->ISR>>16)&1;
    I2C1->ICR|=1<<3;
    
}
*/
void setup(){

    //Wire.begin();
    Serial.begin(115200);
    //i2cset();
    //filter.begin(100);
    //mpu6050_init();
    delay(300);
    pinMode(PB3);
    pinMode(PB3);
}

void loop(){
    analogWrite(PB3,200);
    analogWrite(PB2,200);
  /* 
    rxne=I2C1->ISR&(1<<2);
    if(rxne){
        rxdata=I2C1->RXDR;
    }
    
    Serial.println(rxdata);
    */

/*
    btd.Task();
    
    mpu6050_getdata();    
    filter.updateIMU(xGyro,yGyro,zGyro,xAccl,yAccl,zAccl); 
    roll=filter.getRoll();
    pitch=filter.getPitch();
    yaw=filter.getYaw();

    Serial.println(yaw);
    Serial.print("g");
    Serial.println(zGyro);
    delay(100);
   

    vx=v*cos(theta_*(M_PI/180));
    vy=v*sin(theta_*(M_PI/180));
    
    m[0]=vx*cos(M_PI/2+theta)-vy*sin(M_PI/2+theta)+rz;
    m[1]=-vx*cos(M_PI/2-theta)-vy*sin(M_PI/2-theta)+rz;
    m[2]=-vx*cos(M_PI/2+theta)+vy*sin(M_PI/2+theta)+rz;
    m[3]=vx*cos(M_PI/2-theta)+vy*sin(M_PI/2-theta)+rz;

*/

}

