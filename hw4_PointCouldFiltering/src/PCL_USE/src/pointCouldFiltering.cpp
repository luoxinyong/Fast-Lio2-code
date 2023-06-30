#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>

ros::Publisher downsampled_pub;
void pointCloudCallback(const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
    // --------- 开始你的代码	---------------//
  pcl::PointCloud<pcl::PointXYZI>::Ptr cloud1(new pcl::PointCloud<pcl::PointXYZI>);
  pcl::fromROSMsg(*cloud_msg , *cloud1);
  ROS_INFO("start filter..");
// 用体素滤波先进行下采样，再用直通滤波滤掉x轴的点
  pcl::VoxelGrid<pcl::PointXYZI> voxel_filter;
  voxel_filter.setInputCloud(cloud1);
  voxel_filter.setLeafSize(0.01,0.01,0.01);
  pcl::PointCloud<pcl::PointXYZI>::Ptr voxelfiltered(new pcl::PointCloud<pcl::PointXYZI>);
  voxel_filter.filter(*voxelfiltered);
// 体素滤波完成，进行直通滤波
  pcl::PassThrough<pcl::PointXYZI> pass_filter;
  pass_filter.setInputCloud(voxelfiltered);
  pass_filter.setFilterFieldName("x");
  pass_filter.setFilterLimits(-3.0,3.0);
  // pass_filter.setFilterLimitsNegative(true);
  pcl::PointCloud<pcl::PointXYZI>::Ptr pass_cloud(new pcl::PointCloud<pcl::PointXYZI>);
  pass_filter.filter(*pass_cloud);

  int size = pass_cloud->points.size();
  ROS_INFO("size=",size);
  sensor_msgs::PointCloud2 filter_cloud;  
  pcl::toROSMsg(*pass_cloud,filter_cloud); 
  downsampled_pub.publish(filter_cloud);
    // --------- 结束你的代码	---------------//
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "point_cloud_processing");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("/kitti/velo/pointcloud", 1, pointCloudCallback);
  downsampled_pub = nh.advertise<sensor_msgs::PointCloud2>("/downsampled/cloud", 1);

  ros::spin();

  return 0;
}
