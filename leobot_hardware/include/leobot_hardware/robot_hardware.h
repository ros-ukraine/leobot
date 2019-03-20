/**
* Copyright 2019 ROS Ukraine
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom
* the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
*/

#ifndef LEOBOT_HARDWARE_ROBOT_HARDWARE_H
#define LEOBOT_HARDWARE_ROBOT_HARDWARE_H

#include <memory>
#include <boost/thread/recursive_mutex.hpp>
#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>
#include "leobot_msgs/FirmwareStateRead.h"
#include "leobot_msgs/FirmwareCommandWrite.h"
#include "leobot_hardware/LeobotRobotHardwareConfig.h"

namespace leobot_hardware
{

class LeobotRobotHW : public hardware_interface::RobotHW
{
public:
  LeobotRobotHW();
  virtual ~LeobotRobotHW();
  virtual bool init(ros::NodeHandle &root_nh, ros::NodeHandle &robot_hw_nh);

  virtual void read(const ros::Time &time, const ros::Duration &period);
  virtual void write(const ros::Time &time, const ros::Duration &period);

private:
  void firmwareStateCallback(const leobot_msgs::FirmwareStateRead::ConstPtr &message);
  void dynamicReconfigureCallback(leobot_hardware::LeobotRobotHardwareConfig &config, uint32_t level);

  void setupDynamicReconfigure(ros::NodeHandle& node_handle);
  void setupHardwareInterfaces();

  void fillFirmwareCommandMessageFromConfig(leobot_hardware::LeobotRobotHardwareConfig &config);

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

  leobot_msgs::FirmwareCommandWrite firmware_command_message_;

  std::unique_ptr<dynamic_reconfigure::Server<leobot_hardware::LeobotRobotHardwareConfig>> dynamic_reconfigure_server_;
  dynamic_reconfigure::Server<leobot_hardware::LeobotRobotHardwareConfig>::CallbackType reconfigure_callback_;
  leobot_hardware::LeobotRobotHardwareConfig default_dynamic_server_config_;

  boost::recursive_mutex dynamic_reconfigure_mutex_;
};

}  // namespace leobot_hardware

#endif  // LEOBOT_HARDWARE_ROBOT_HARDWARE_H
