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

//    void LeobotRobotHW::jointStateCallback(const leobot_msgs::MotorsJointState::ConstPtr& message)
//    {
//      std::lock_guard<std::mutex> lock(this->joint_states_update_mutex);

//      hardware_motor_position[0] = message->left_joint_position;
//      hardware_motor_velocity[0] = message->left_joint_velocity;
//      hardware_motor_effort[0] = message->left_joint_effort;

//      hardware_motor_position[1] = message->right_joint_position;
//      hardware_motor_velocity[1] = message->right_joint_velocity;
//      hardware_motor_effort[1] = message->right_joint_effort;
//    }

  bool LeobotRobotHW::init(ros::NodeHandle& root_nh)
  {
    // publish_motor_velocities = root_nh.advertise<leobot_msgs::SetMotorsVelocity>("set_motors_velocity", 1000);
    // motors_joint_state = root_nh.subscribe("motors_joint_state", 1000, &LeobotRobotHW::jointStateCallback, this);

    // hardware_interface::JointStateHandle left_wheel_joint_state_handle("back_left_wheel_joint", &position[0],
    //     &velocity[0], &effort[0]);
    // joint_state_interface.registerHandle(left_wheel_joint_state_handle);

    // hardware_interface::JointStateHandle right_wheel_joint_state_handle("back_right_wheel_joint", &position[1],
    //     &velocity[1], &effort[1]);
    // joint_state_interface.registerHandle(right_wheel_joint_state_handle);

    // registerInterface(&joint_state_interface);

    // hardware_interface::JointHandle left_wheel_joint_velocity_handler(
    //     joint_state_interface.getHandle("back_left_wheel_joint"), &command[0]);
    // joint_velocity_interface.registerHandle(left_wheel_joint_velocity_handler);
    // hardware_interface::JointHandle right_wheel_joint_velocity_handler(
    //     joint_state_interface.getHandle("back_right_wheel_joint"), &command[1]);
    // joint_velocity_interface.registerHandle(right_wheel_joint_velocity_handler);

    // registerInterface(&joint_velocity_interface);
  }

  void LeobotRobotHW::read(const ros::Time& time, const ros::Duration& period)
  {
    // std::lock_guard<std::mutex> lock(this->joint_states_update_mutex);
    // for (unsigned i = 0; i != JOINTS_COUNT; ++i) {
    //   position[i] = hardware_motor_position[i];
    //   velocity[i] = hardware_motor_velocity[i];
    //   effort[i] = hardware_motor_effort[i];
    // }
  }

  void LeobotRobotHW::write(const ros::Time& time, const ros::Duration& period)
  {
    // leobot_msgs::SetMotorsVelocity message;
    // message.left_joint_velocity = command[0];
    // message.right_joint_velocity = command[1];
    // publish_motor_velocities.publish(message);
  }

}  // leobot_hardware