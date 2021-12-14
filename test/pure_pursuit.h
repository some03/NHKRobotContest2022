#ifndef PURSUIT
#define PURSUIT

#include<math.h>
#include<iostream>
#include<vector>
#include<stdio.h>
#include<algorithm>
#include<tuple>
#include<climits>

#define USESIMULATION
#define Lfc 0.3//次点までの距離
#define WB 0
#define k 0.1
#define kp 0.02

double  dt=0.1;
int i=0;
class state{
    public:
        state(double initx,double inity,double inityaw,double innitv);
        void update(double v_,double delta);
        void update(double x,double y,double delta);
        double calc_distance(double point_x,double point_y,int a);
        double x,y,yaw,v;
        double rear_x,rear_y;


        std::vector<double>tx;
        std::vector<double>ty;
        std::vector<double>testy;
        std::vector<double>testx;
};
class target_course{
    public:
        target_course(std::vector<double>x,std::vector<double>y);
        std::tuple<int,double>search_target_index(state st);
        std::vector<double>cx;
        std::vector<double>cy;
        double distance_this_index;
        double distance_next_index;    
    private:    
        int old_point_index;
        int ind=0;

};
state::state(double initx,double inity,double inityaw,double initv){
    
    x=initx;
    y=inity;
    v=initv;
    yaw=inityaw;

    rear_x=x-(WB/2);
    rear_y=y-(WB/2);
}
#ifdef USESIMULATION
    void state::update(double v_,double alpha){
        v=v_;
        yaw=alpha;
        x+=v*cos(yaw)*dt;
        y+=v*sin(yaw)*dt;
        rear_x=x-(WB/2);
        rear_y=y-(WB/2);
        tx.push_back(rear_x);
        ty.push_back(rear_y);
/*
        std::cout<<"x:";
        std::cout<<x<<endl;
        std::cout<<"y:";
        std::cout<<y<<endl;
*/
    }
#endif
#ifdef USEODOMETRY
    void state::update(double x,double y,double alpha){
        yaw=alpha;
        rear_x=x-(WB/2);
        rear_y=y-(WB/2);
        tx.push_back(rear_x);
        ty.push_back(rear_y);
    }
#endif
double state::calc_distance(double point_x,double point_y ,int a){
    double dx=rear_x-point_x;
    double dy=rear_y-point_y;
    return hypot(dx,dy);
}

target_course::target_course(std::vector<double>x,std::vector<double>y){
    for(int i=0;i<y.size();i++){
        cx.push_back(x[i]);
        cy.push_back(y[i]);
    }
    old_point_index=INT_MAX;
    //std::cout<<"constractor";
}

std::tuple<int,double>target_course::search_target_index(state st){
    //最短点を探す
   if(old_point_index==INT_MAX){
        double dx;
        double dy;
        std::vector<int>d;

        for(int i=0;i<cx.size();i++){
            dx=st.x-cx[i];
            dy=st.y-cy[i];
            d.push_back(hypot(dx,dy));
        }
        std::vector<int>::iterator minIt=std::min_element(d.begin(),d.end());
        ind=std::distance(d.begin(),minIt);

        old_point_index=ind;

    } 

   
    else{
       //ind=old_point_index;
       distance_this_index=st.calc_distance(cx[ind],cy[ind],1); 

       while(true){

            distance_next_index=st.calc_distance(cx[ind+1],cy[ind+1],2);
            if(distance_this_index<distance_next_index){
                //std::cout<<distance_next_index<<endl;
                break;
            }
            else if(ind+1<cx.size()){
                ind++;
                //std::cout<<ind<<endl;
            }
            else{
                ind=ind;
            }
            distance_this_index=distance_next_index;
        }
        //old_point_index=ind;
    }
    
    //心臓-----------------------------------------
    
    while(Lfc>st.calc_distance(cx[ind],cy[ind],4)){
        if(ind+1>=cx.size())break;
        ind+=1;
        //std::cout<<ind<<endl;
        //std::cout<<st.calc_distance(cx[ind],cy[ind],4)<<endl;
        //std::cout<<ind;
        //std::cout<<";";
    }
    return std::forward_as_tuple(ind,Lfc);
    
}


//functions-----------------------------------------------------------------


double speed_control(double target,double current){
    double speed=kp*(target-current);
    return speed;
}

std::tuple<int,double> pursuit_control(state st,target_course& trajectory,int pind){

    int  Ind;
    double lf;
    std::tie(Ind,lf)=trajectory.search_target_index(st);


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
    double alpha=atan2(ty-st.rear_y,tx-st.rear_x);
    //double delta=atan2(2*5*sin(alpha)/Lfc,1.0); 
    return std::forward_as_tuple(Ind,alpha);
}
#endif

