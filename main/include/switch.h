#ifndef SWITCH
#define SEITCH

#include<cubic_spline.h>
#include<pure_pursuit.h>
#include<controller.h>
#include<auto.h>
#include<iostream>
#include<vector>
#include<Wire.h>

#define MD1ADDR 4
#define MD2ADDR 5
#define MD3ADDR 6
#define MD4ADDR 7
#define MD5ADDR 8
#define MD6ADDR 9
#define MD7ADDR 10

class Auto
{
    public:

        std::vector<double>rootx;
        std::vector<double>rooty;
        int make_root(std::vector<double>pointx,std::vector<double>pointy)
        {
            CubicSpline cbx(pointx);    
            CubicSpline cby(pointy);

            for(double i=0;i<pointx.size();i++){
                rootx.push_back(cbx.Calc(i));
                rooty.push_back(cby.Calc(i));
            }
        }
        int run(double initx,double inity,double initv)
        {
            double lf; 
            int target_ind;
            int8_t mt1=0,mt2=0,mt3=0;
            long enca,encb,encc;
            long cnt1=0,cnt2=0,cnt3=0;
            long nowx,nowy,nowyaw;
            int delta;
            int cl=0.7;//circumference_length
            int pa=10;//parameter
            
            State state(initx,inity,initv);
            int last_ind=rootx.size()-1;
            TargetCourse target_course(rootx,rooty);
            std::tie(target_ind,lf)=target_course.search_target_index(state);
            std::tie(enca,encb,encc)=get_rotational_speed(1);  
            
            while(last_ind>target_ind){
                
                std::tie(enca,encb,encc)=get_rotational_speed(0);
                cnt1+=(enca/1)*cl;
                cnt2+=(encb/1)*cl;
                cnt3+=(encc/1)*cl;

                nowx=-cnt2+(cnt1*sqrt(3)/2)+(cnt3*sqrt(3)/2);
                nowy=-cnt1/2+cnt3/2;

                std::tie(target_ind,delta)=pursuit_control(state,target_course,target_ind);
                state.update(nowx,nowy,delta);

                int8_t x=pa*cos(delta);
                int8_t y=pa*sin(delta);

                mt1=-x;
                mt2=(x/2)-(sqrt(3)/2)*y;
                mt3=(x/2)+(sqrt(3)/2)*y;

                
                if(mt1<0) mt1=~abs(mt1),mt1+=0b1;
                if(mt2<0) mt2=~abs(mt2),mt2+=0b1;
                if(mt3<0) mt3=~abs(mt3),mt3+=0b1;
                
                Wire.beginTransmission(MD1ADDR);
                Wire.write(mt1);
                Wire.endTransmission();
                
                Wire.beginTransmission(MD2ADDR);
                Wire.write(mt2);
                Wire.endTransmission();

                Wire.beginTransmission(MD3ADDR);
                Wire.write(mt3);
                Wire.endTransmission();

                
            }

            Wire.beginTransmission(MD1ADDR);
            Wire.write(0);
            Wire.endTransmission();
            
            Wire.beginTransmission(MD2ADDR);
            Wire.write(0);
            Wire.endTransmission();

            Wire.beginTransmission(MD3ADDR);
            Wire.write(0);
            Wire.endTransmission();
        }
};

class act1
{
    public:
        int act()
        {
            return 5;
        }
};
class act2
{
    public:
        int act()
        {
            return 5;
        }
};
#endif
