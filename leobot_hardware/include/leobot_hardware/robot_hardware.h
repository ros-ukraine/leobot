#ifndef LEOBOT_HARDWARE_ROBOT_HARDWARE_H
#define LEOBOT_HARDWARE_ROBOT_HARDWARE_H

#include <mutex>
#include <ros/ros.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>
#include "leobot_msgs/FirmwareStateRead.h"
#include "leobot_msgs/FirmwareCommandWrite.h"

namespace leobot_hardware
{

class LeobotRobotHW : public hardware_interface::RobotHW
{
public:
  LeobotRobotHW();
  virtual ~LeobotRobotHW();
  virtual bool init(ros::NodeHandle& root_nh);
  void read(const ros::Time& time, const ros::Duration& period);
  void write(const ros::Time& time, const ros::Duration& period);

private:
  void firmwareStateCallback(const leobot_msgs::FirmwareStateRead::ConstPtr& message);

  hardware_interface::JointStateInterface joint_state_interface;
  hardware_interface::VelocityJointInterface joint_velocity_interface;

  ros::Subscriber state_subscriber_;
  ros::Publisher command_publisher_;

  static const int JOINTS_COUNT = 4;

  double command[JOINTS_COUNT];
  double position[JOINTS_COUNT];
  double velocity[JOINTS_COUNT];
  double effort[JOINTS_COUNT];

  double hardware_motor_position[JOINTS_COUNT];
  double hardware_motor_velocity[JOINTS_COUNT];
  double hardware_motor_effort[JOINTS_COUNT];
};

}  // leobot_hardware

#endif  // LEOBOT_HARDWARE_ROBOT_HARDWARE_H