/*
 * cubic_spline.h
 */
#ifndef SPLINE_H
#define SPLINE_H
#include<vector>
#include<math.h>
#include<iostream>
using namespace std;

struct point{
    std::vector<double>x;
    std::vector<double>y;
    std::vector<double>angle;
    std::vector<double>curvature;
    std::vector<double>velocity;
};

class cubic_spline{
    public:
        cubic_spline(const vector<double> y);
        double calc(double t,point p,point* p_);
        void   calc_curvature(double t, point* p_);
        double accl;
        void initParameter(const vector<double> y);
    private:
        vector<double>a_;
        vector<double>b_;
        vector<double>c_;
        vector<double>d_;
        vector<double>w_;

};

cubic_spline::cubic_spline(const vector<double>y){
    initParameter(y);
}
void cubic_spline::initParameter(const vector<double>y){
    int data=y.size()-1;

    for(int i=0;i<=data;i++){
        a_.push_back(y[i]);
    }
    for(int i=0;i<data;i++){
        if(i==0){
            c_.push_back(0.0);
        }
        else if(i==data){
            c_.push_back(0.0);
        }
        else {
            c_.push_back(3.0*(a_[i-1]-2.0*a_[i]+a_[i+1]));
        }
    }

    for(int i=0;i<data;i++){
        if(i==0){
            w_.push_back(0.0);
        }
        else{
            double tmp=4.0-w_[i-1];
            c_[i]=(c_[i]-c_[i-1])/tmp;
            w_.push_back(1.0/tmp);
        }

    }
    for (int i=(data-1);i>0;i--){
        c_[i]=c_[i]-c_[i+1]*w_[i];
    }

    for(int i=0;i<=data;i++){
        if(i==data){
            d_.push_back(0.0);
            b_.push_back(0.0);
        }
        else{
            d_.push_back((c_[i+1]-c_[i])/3.0);
            b_.push_back(a_[i+1]-a_[i]-c_[i]-d_[i]);
        }
    }
}
double cubic_spline::calc(double t,point p,point* p_){
    int j=int(floor(t));
    if(j<0){
        j=0;
    }
    else if(j>=a_.size()){
        j=(a_.size()-1);
    }
    if(j<a_.size()-1){
        if(p.angle[j]!=p.angle[j+1]){
            p_->angle.push_back(p.angle[j+1]-p.angle[j]);
        }
    }
    double dt=t-j;
    double result=a_[j]+(b_[j]+(c_[j]+d_[j]*dt)*dt)*dt;
    return result;
}

void cubic_spline::calc_curvature(double t,point* p_){
    int j=int(floor(t));
    if(j<0){
        j=0;
    }
    else if(j>=a_.size()){
        j=(a_.size()-1);
    }
    double dt=(t-j);
    double e=1+pow((b_[j]+(2*c_[j]+3*d_[j]*dt)*dt),2);
    e=sqrt(pow(e,3));
    p_->curvature.push_back((2*c_[j]+6*d_[j]*dt)/e);

}


#endif
