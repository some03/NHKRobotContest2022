#ifndef JOINT_STATE_PUB
#define JOINT_STATE_PUB
#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<sensor_msgs/Imu.h>
#include<std_msgs/Float64.h>
#include<tf/transform_datatypes.h>
#include<math.h>

#define length 14//機体中心からホイールまでの距離
class joint_pub{
    public:
        void publish(int x,int y,int z);
    private:
        ros::NodeHandle nh;
        ros::Publisher mt[4]={
        nh.advertise<std_msgs::Float64>("/odm_robot/joint_controller0/commond",10),
        nh.advertise<std_msgs::Float64>("/odm_robot/joint_controller3/commond",10),
        nh.advertise<std_msgs::Float64>("/odm_robot/joint_controller2/commond",10),
        nh.advertise<std_msgs::Float64>("/odm_robot/joint_controller1/commond",10)

    };

    void cmdcb(const geometry_msgs::Twist::ConstPtr& cmdmsg);
    ros::Subscriber cmdsub=nh.subscribe("cmd_vel",10,&joint_pub::cmdcb,this);
    void imucb(const sensor_msgs::Imu& imumsg);
    ros::Subscriber imusub=nh.subscribe("imu/data",10,&joint_pub::imucb,this);

    float m[4]; 
    double roll,pitch,theta=0;
    

};



void joint_pub::imucb(const sensor_msgs::Imu& imumsg){
    double qx,qy,qz,qw;

    qx=imumsg.orientation.x;
    qy=imumsg.orientation.y;
    qz=imumsg.orientation.z;
    qw=imumsg.orientation.w;

    tf::Quaternion quat(qx,qy,qz,qw);
    tf::Matrix3x3(quat).getRPY(roll,pitch,theta);
    
}
void joint_pub::publish(int x,int y,int z){

    m[0]=x*cos(M_PI/2+theta)-y*sin(M_PI/2+theta)+length*z;
    m[1]=-x*cos(M_PI/2-theta)-y*sin(M_PI/2-theta)+length*z;
    m[2]=-x*cos(M_PI/2+theta)+y*sin(M_PI/2+theta)+length*z;
    m[3]=x*cos(M_PI/2-theta)+y*sin(M_PI/2-theta)+length*z;

    for(int i=0;i<4;i++){
        std_msgs::Float64 jointmsg;
        jointmsg.data=m[i];
        mt[i].publish(jointmsg);
        ROS_INFO("%lf",jointmsg);
    }

    
}
void joint_pub::cmdcb(const geometry_msgs::Twist::ConstPtr& cmdmsg){
    geometry_msgs::Vector3 linear=cmdmsg->linear;
    geometry_msgs::Vector3 angular=cmdmsg->angular;
    
    ROS_INFO("ok %s");
//    publish(linear.x,linear.y,angular.z);
}

#endif
