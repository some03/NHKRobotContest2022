#include<matplotlibcpp.h>
#include"spline.h"
#include"pure_pursuit.h"
#include<vector>
namespace plt=matplotlibcpp;
#define vel_max 2

int main(){
    int r=500;//WB
    //経路生成-----------------------------------
    std::vector<double>point_x{0,1,2,3};
    std::vector<double>point_y{2.7,6,5,6.5};
    std::vector<double>point_angle{0,0,0,70};
    
    point prep={point_x,point_y,point_angle};
    point afterp;

    cubic_spline cx(prep.x);
    cubic_spline cy(prep.y);
    
    for(double i=0.0;i<point_x.size();i+=0.1){
        afterp.x.push_back(cx.calc(i,prep,&afterp));
        afterp.y.push_back(cy.calc(i,prep,&afterp));
    }

    //曲率計算----------------------------------------------- 
    for(double i=0.0;i<point_y.size();i+=0.1){
        cy.calc_curvature(i,&afterp);
    }
    //速度計算-----------------------------------------------
    for(int i=0;i<afterp.y.size();i++){

       if(abs(afterp.curvature[i])>4)afterp.velocity.push_back(sqrt(0.2*9.8*(1/abs(afterp.curvature[i]))));
       else afterp.velocity.push_back(vel_max);
       std::cout<<abs(afterp.curvature[i]);
       std::cout<<":";
       std::cout<<afterp.velocity[i]<<endl;
       
    }
    //経路追従----------------------------------------------

    state st(1500,6000,0,0);

    double last_ind=afterp.x.size()-1;
    double target_ind=0,lf;
    double delta=0;
    float t=0;
    double m[4];
    double v,z,nowx,nowy,nowz;
    target_course tc(afterp.x,afterp.y);

    std::tie(target_ind,lf)=tc.search_target_index(st);
    
    while(t<30&&last_ind>target_ind){
        /*
        std::cout<<target_ind;
        std::cout<<":";
        std::cout<<delta<<std::endl;
       */ 
        std::tie(target_ind,delta)=pursuit_control(st,tc,target_ind);

        //速度-------------------------------------
        v=afterp.velocity[target_ind];
        //-----------------------------------------------------

        double vx=v*cos(delta);
        double vy=v*sin(delta);

        //角速度-------------------------------------------------
        if(afterp.angle[target_ind]!=0){
            z=afterp.angle[target_ind]-delta/0.1;//仮
        }
        //-----------------------------------------------------
       
        m[0]=vx*cos(M_PI/4+delta)-vy*sin(M_PI/4+delta)+r*z;
        m[1]=-vx*cos(M_PI/4-delta)-vy*sin(M_PI/4-delta)+r*z;
        m[2]=-vx*cos(M_PI/4+delta)+vy*sin(M_PI/4+delta)+r*z;
        m[3]=vx*cos(M_PI/4-delta)+vy*sin(M_PI/4-delta)+r*z;
       
        nowx=m[0]*cos(M_PI/4+delta)-m[1]*cos(M_PI/4-delta)-m[2]*cos(M_PI/4+delta)+m[3]*cos(M_PI/4-delta);
        nowy=-m[0]*sin(M_PI/4+delta)-m[1]*sin(M_PI/4-delta)+m[2]*sin(M_PI/4+delta)+m[3]*sin(M_PI/4-delta);

        st.update(500,delta);
        
        t+=0.1;
    }

    


    
    plt::named_plot("spline",afterp.x,afterp.y,"-b");
    plt::named_plot("velocity",afterp.x,afterp.velocity,"-r");
    plt::named_plot("curvature",afterp.x,afterp.curvature,"-g");
    //plt::named_plot("cource",st.tx,st.ty,"r");
    //plt::named_plot("test",st.testx,st.testy,"xg");
    plt::legend();
    plt::axis("equal");
    plt::grid(true);
    plt::show();
    

    return 0;
}

