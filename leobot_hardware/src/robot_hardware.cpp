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

  void LeobotRobotHW::fillFirmwareCommandMessageFromConfig(leobot_hardware::LeobotRobotHardwareConfig &config)
  {
    firmware_command_message_.motor_1_p = config.motor_1_p;
    firmware_command_message_.motor_1_i = config.motor_1_i;
    firmware_command_message_.motor_1_d = config.motor_1_d;

    firmware_command_message_.motor_2_p = config.motor_2_p;
    firmware_command_message_.motor_2_i = config.motor_2_i;
    firmware_command_message_.motor_2_d = config.motor_2_d;
    
    firmware_command_message_.motor_3_p = config.motor_3_p;
    firmware_command_message_.motor_3_i = config.motor_3_i;
    firmware_command_message_.motor_3_d = config.motor_3_d;

    firmware_command_message_.motor_4_p = config.motor_4_p;
    firmware_command_message_.motor_4_i = config.motor_4_i;
    firmware_command_message_.motor_4_d = config.motor_4_d;
  }

  void LeobotRobotHW::dynamicReconfigureCallback(leobot_hardware::LeobotRobotHardwareConfig &config, uint32_t level)
  {
    fillFirmwareCommandMessageFromConfig(config);
  }

  void  LeobotRobotHW::setupHardwareInterfaces()
  {
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
        joint_state_interface.getHandle("rear_right_wheel_motor_joint"), &command[2]);
    joint_velocity_interface.registerHandle(rear_right_wheel_joint_velocity_handler);

    hardware_interface::JointHandle rear_left_wheel_joint_velocity_handler(
        joint_state_interface.getHandle("rear_left_wheel_motor_joint"), &command[3]);
    joint_velocity_interface.registerHandle(rear_left_wheel_joint_velocity_handler);

    registerInterface(&joint_velocity_interface);
  }

  void  LeobotRobotHW::setupDynamicReconfigure()
  {
    ros::NodeHandle dynamic_node;
    dynamic_reconfigure_server_.reset(new dynamic_reconfigure::Server<leobot_hardware::LeobotRobotHardwareConfig>(
      dynamic_reconfigure_mutex_, dynamic_node));
    reconfigure_callback_ = boost::bind(&LeobotRobotHW::dynamicReconfigureCallback, this, _1, _2);

    default_dynamic_server_config_.__fromServer__(dynamic_node);
    dynamic_reconfigure_server_->setCallback(reconfigure_callback_);

    fillFirmwareCommandMessageFromConfig(default_dynamic_server_config_);
  }

  bool LeobotRobotHW::init(ros::NodeHandle& root_nh)
  {
    command_publisher_ = root_nh.advertise<leobot_msgs::FirmwareCommandWrite>("firmware_command_write", 10);
    state_subscriber_ = root_nh.subscribe("firmware_state_read", 1, &LeobotRobotHW::firmwareStateCallback, this);

    setupHardwareInterfaces();
    setupDynamicReconfigure();
  }

  void LeobotRobotHW::read(const ros::Time& time, const ros::Duration& period)
  {
  }

  void LeobotRobotHW::write(const ros::Time& time, const ros::Duration& period)
  {
    boost::recursive_mutex::scoped_lock lock(dynamic_reconfigure_mutex_);

    firmware_command_message_.motor_1_velocity_command = command[0];
    firmware_command_message_.motor_2_velocity_command = command[1];
    firmware_command_message_.motor_3_velocity_command = command[2];
    firmware_command_message_.motor_4_velocity_command = command[3];

    command_publisher_.publish(firmware_command_message_);
  }

}  // leobot_hardware