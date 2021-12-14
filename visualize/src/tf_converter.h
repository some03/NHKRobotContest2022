#ifndef TF_CONVERTER
#define TF_CONVERTER
#include<ros/ros.h>
#include<nav_msgs/Odometry.h>
#include<tf/transform_broadcaster.h>
#include<string>
#include<math.h>

class tf_converter{
    public:
        ros::NodeHandle nh;
        tf::TransformBroadcaster br;

        void odom_callback(const nav_msgs::Odometry& odommsg);
        ros::Subscriber sub=nh.subscribe("/tracker",10,&tf_converter::odom_callback,this);

};

void tf_converter::odom_callback(const nav_msgs::Odometry& odommsg){
    tf::Transform transform;
    tf::poseMsgToTF(odommsg.pose.pose,transform);

    br.sendTransform(tf::StampedTransform(transform,odommsg.header.stamp,"odom",odommsg.child_frame_id));
}
#endif
