#include"joint_state_pub.h"
#include"tf_converter.h"
//手動の場合は速度角速度　自動は移動距離回転角度

int main(int argc,char**argv ){
    ros::init(argc,argv,"simulation");
    joint_pub jp;
    tf_converter tc;
    ros::Rate loop_rate(10);
    
    ros::spin();
    return 0;
    
}


