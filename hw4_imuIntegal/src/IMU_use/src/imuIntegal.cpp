#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include "sophus/so3.h"

Eigen::Vector3d pos = Eigen::Vector3d(0,0,0);
Sophus::SO3     rot = Sophus::SO3(Eigen::Matrix3d::Identity());
Eigen::Vector3d vel = Eigen::Vector3d(0,0,0);
Eigen::Vector3d bg = Eigen::Vector3d(0,0,0);
Eigen::Vector3d ba = Eigen::Vector3d(0,0,0);
Eigen::Vector3d grav = Eigen::Vector3d(0,0,-9.8);
double last_timeStamp;
bool first_imu = true;

void imuCallback(const sensor_msgs::Imu::ConstPtr &msg_in)
{
  //------------- 开始你的代码 --------------------//
  if(first_imu)
  {
    first_imu = false;
    last_timeStamp = msg_in->header.stamp.toSec(); 
    return;
  }
    double dt = msg_in->header.stamp.toSec()-last_timeStamp;
    Eigen::Vector3d w_m = Eigen::Vector3d(0,0,0);
      w_m[0] = msg_in->angular_velocity.x;
      w_m[1] = msg_in->angular_velocity.y;
      w_m[2] = msg_in->angular_velocity.z;
    rot *= Sophus::SO3::exp((w_m-bg)*dt);

    pos += vel*dt;

    Eigen::Vector3d a_m = Eigen::Vector3d(0,0,0);
    a_m[0] = msg_in->linear_acceleration.x;
    a_m[1] = msg_in->linear_acceleration.y;
    a_m[2] = msg_in->linear_acceleration.z;
    vel += (rot*(a_m-ba)+grav)*dt;
  //------------- 结束你的代码 --------------------//
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "imu_integal");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("/imu/data", 10000, imuCallback);
  ros::spin();

  return 0;
}
