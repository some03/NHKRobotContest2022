#ifndef PURSUIT
#define PURSUIT

#include<math.h>
#include<iostream>
#include<vector>
#include<stdio.h>
#include<algorithm>
#include<tuple>
#include<climits>

#define Lfc 1
#define WB 0.7
#define k 0.1
#define kp 0.02

double  dt=0.1;

class State{
    public:
        State(double initx,double inity,double inityaw,double innitv);
        void update(double v_,double delta);
        double calc_distance(double point_x,double point_y,int a);
        double x,y,yaw,v;
        double rear_x,rear_y;


        std::vector<double>tx;
        std::vector<double>ty;
};

class TargetCourse{
    public:
        TargetCourse(std::vector<double>x,std::vector<double>y);
        std::tuple<int,double>search_target_index(State state);
        std::vector<double>cx;
        std::vector<double>cy;
        double distance_this_index;
        double distance_next_index;    
    private:    
        int old_point_index;
        int ind=0;

};

State::State(double initx,double inity,double inityaw,double initv){
    
    this->x=initx;
    this->y=inity;
    this->v=initv;
    this->yaw=inityaw;

    rear_x=x-(WB/2);
    rear_y=y-(WB/2);
}

void State::update(double v_,double alpha){
    this->x+=v*cos(yaw)*dt;
    this->y+=v*sin(yaw)*dt;
    this->v+=v_*dt;
    this->yaw=alpha;

    rear_x=this->x-(WB/2);
    rear_y=this->y-(WB/2);
    
    
    tx.push_back(this->x);
    ty.push_back(this->y);
}
double State::calc_distance(double point_x,double point_y ,int a){
    double dx=rear_x-point_x;
    double dy=rear_y-point_y;
/*
    std::cout<<"X:"<<point_x<<std::endl;
    std::cout<<"Y:"<<point_y<<std::endl;
    std::cout<<"a:"<<a<<std::endl;
    std::cout<<" "<<std::endl;
    */
    return hypot(dx,dy);
}

TargetCourse::TargetCourse(std::vector<double>x,std::vector<double>y){
    for(int i=0;i<y.size();i++){
        cx.push_back(x[i]);
        cy.push_back(y[i]);
    }
    old_point_index=INT_MAX;
    //std::cout<<"constractor";
}

std::tuple<int,double>TargetCourse::search_target_index(State state){
    //最短点を探す
   if(old_point_index==INT_MAX){
        double dx;
        double dy;
        std::vector<int>d;

        for(int i=0;i<cx.size();i++){
            dx=state.x-cx[i];
            dy=state.y-cy[i];
            d.push_back(hypot(dx,dy));
        }
        std::vector<int>::iterator minIt=std::min_element(d.begin(),d.end());
        ind=std::distance(d.begin(),minIt);

        old_point_index=ind;

    } 

   
    else{
       ind=old_point_index;
       distance_this_index=state.calc_distance(cx[ind],cy[ind],1); 

       while(true){

            distance_next_index=state.calc_distance(cx[ind+1],cy[ind+1],2);
            if(distance_this_index<distance_next_index)break;
            
            if(ind+1<cx.size()){
                ind++;
            }
            else{
                ind=ind;
            }
            distance_this_index=distance_next_index;
        }
        old_point_index=ind;
    }
    

    double lf=k*state.v+Lfc;
    
    while(lf>state.calc_distance(cx[ind],cy[ind],4)){
        if(ind+1>=cx.size())break;
        ind+=1;
    }
    
    return std::forward_as_tuple(ind,lf);
}


//functions-----------------------------------------------------------------


double speed_control(double target,double current){
    double speed=kp*(target-current);
    return speed;
}

std::tuple<int,double> pursuit_control(State state,TargetCourse& trajectory,int pind){

    int  Ind;
    double lf;
    std::tie(Ind,lf)=trajectory.search_target_index(state);


    double tx,ty;

    if(pind>=Ind){
        Ind=pind;

    }
    
    if(Ind<trajectory.cx.size()){
        tx=trajectory.cx[Ind];    
        ty=trajectory.cy[Ind];    
    }
    if(Ind>trajectory.cx.size()){
        tx=trajectory.cx[trajectory.cx.size()-1];
        ty=trajectory.cy[trajectory.cy.size()-1];
        Ind=trajectory.cx.size()-1;
    }

    double alpha=atan2(ty-state.rear_y,tx-state.rear_x);
  //  double delta=atan2(2.0*WB*sin(alpha)/lf,1.0);
  //  double dist=hypot(tx,ty);
    
   // double relx=dist*cos(alpha);
   // double rely=dist*sin(alpha);
    return std::forward_as_tuple(Ind,alpha);
}
#endif

