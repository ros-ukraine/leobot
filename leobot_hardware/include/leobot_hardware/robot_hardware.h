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

// private:
//   void jointStateCallback(const leobot_msgs::MotorsJointState::ConstPtr& message);

//   hardware_interface::JointStateInterface joint_state_interface;
//   hardware_interface::VelocityJointInterface joint_velocity_interface;

//   ros::Subscriber motors_joint_state;
//   ros::Publisher publish_motor_velocities;

//   std::mutex joint_states_update_mutex;

//   static const int JOINTS_COUNT = 2;

//   double command[JOINTS_COUNT];
//   double position[JOINTS_COUNT];
//   double velocity[JOINTS_COUNT];
//   double effort[JOINTS_COUNT];

//   double hardware_motor_position[JOINTS_COUNT];
//   double hardware_motor_velocity[JOINTS_COUNT];
//   double hardware_motor_effort[JOINTS_COUNT];
};

}  // leobot_hardware

#endif  // LEOBOT_HARDWARE_ROBOT_HARDWARE_H