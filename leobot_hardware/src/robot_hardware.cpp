#include "leobot_hardware/robot_hardware.h"
#include <std_msgs/Float32.h>
#include <hardware_interface/robot_hw.h>
#include <string>
#include <vector>

namespace leobot_hardware
{

  LeobotRobotHW::LeobotRobotHW()
  {
  }

  LeobotRobotHW::~LeobotRobotHW()
  {
  }

  void LeobotRobotHW::firmwareStateCallback(const leobot_msgs::FirmwareStateRead::ConstPtr& message)
  {
    hardware_motor_position[0] = message->motor_1_position;
    hardware_motor_velocity[0] = message->motor_1_velocity;
    hardware_motor_effort[0] = message->motor_1_effort;

    hardware_motor_position[1] = message->motor_2_position;
    hardware_motor_velocity[1] = message->motor_2_velocity;
    hardware_motor_effort[1] = message->motor_2_effort;

    hardware_motor_position[2] = message->motor_3_position;
    hardware_motor_velocity[2] = message->motor_3_velocity;
    hardware_motor_effort[2] = message->motor_3_effort;

    hardware_motor_position[3] = message->motor_4_position;
    hardware_motor_velocity[3] = message->motor_4_velocity;
    hardware_motor_effort[3] = message->motor_4_effort;
  }

  bool LeobotRobotHW::init(ros::NodeHandle& root_nh)
  {
    this->command_publisher_ = root_nh.advertise<leobot_msgs::FirmwareCommandWrite>("firmware_command_write", 10);
    this->state_subscriber_ = root_nh.subscribe("firmware_state_read", 1, &LeobotRobotHW::firmwareStateCallback, this);

    hardware_interface::JointStateHandle front_right_wheel_joint_state_handle("front_right_wheel_motor_joint", 
      &position[0], &velocity[0], &effort[0]);
    joint_state_interface.registerHandle(front_right_wheel_joint_state_handle);

    hardware_interface::JointStateHandle front_left_wheel_joint_state_handle("front_left_wheel_motor_joint", 
      &position[1], &velocity[1], &effort[1]);
    joint_state_interface.registerHandle(front_left_wheel_joint_state_handle);

    hardware_interface::JointStateHandle rear_right_wheel_joint_state_handle("rear_right_wheel_motor_joint", 
      &position[2], &velocity[2], &effort[2]);
    joint_state_interface.registerHandle(rear_right_wheel_joint_state_handle);

    hardware_interface::JointStateHandle rear_left_wheel_joint_state_handle("rear_left_wheel_motor_joint", 
      &position[3], &velocity[3], &effort[3]);
    joint_state_interface.registerHandle(rear_left_wheel_joint_state_handle);

    registerInterface(&joint_state_interface);

    hardware_interface::JointHandle front_right_wheel_joint_velocity_handler(
        joint_state_interface.getHandle("front_right_wheel_motor_joint"), &command[0]);
    joint_velocity_interface.registerHandle(front_right_wheel_joint_velocity_handler);

    hardware_interface::JointHandle front_left_wheel_joint_velocity_handler(
        joint_state_interface.getHandle("front_left_wheel_motor_joint"), &command[1]);
    joint_velocity_interface.registerHandle(front_left_wheel_joint_velocity_handler);

    hardware_interface::JointHandle rear_right_wheel_joint_velocity_handler(
        joint_state_interface.getHandle("frear_right_wheel_motor_joint"), &command[2]);
    joint_velocity_interface.registerHandle(rear_right_wheel_joint_velocity_handler);

    hardware_interface::JointHandle rear_left_wheel_joint_velocity_handler(
        joint_state_interface.getHandle("rear_left_wheel_motor_joint"), &command[3]);
    joint_velocity_interface.registerHandle(rear_left_wheel_joint_velocity_handler);

    registerInterface(&joint_velocity_interface);
  }

  void LeobotRobotHW::read(const ros::Time& time, const ros::Duration& period)
  {
  }

  void LeobotRobotHW::write(const ros::Time& time, const ros::Duration& period)
  {
    leobot_msgs::FirmwareCommandWrite command_message;

    command_message.motor_1_velocity_command = command[0];
    // command_message.motor_1_p = params.d;

    command_message.motor_2_velocity_command = command[1];
    // command_message.motor_2_p = params.d;

    command_message.motor_3_velocity_command = command[2];
    // command_message.motor_3_p = params.d;

    command_message.motor_4_velocity_command = command[3];
    // command_message.motor_4_p = params.d;
    
    this->command_publisher_.publish(command_message);
  }

}  // leobot_hardware