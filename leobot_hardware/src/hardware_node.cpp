#include "leobot_hardware/robot_hardware.h"
#include <controller_manager/controller_manager.h>
#include <hardware_interface/actuator_state_interface.h>
#include <ros/callback_queue.h>

using leobot_hardware::LeobotRobotHW;

int main(int argc, char **argv)
{
  std::string node_name = "leobot_hardware_node";

  ros::init(argc, argv, node_name);
  ros::NodeHandle node_handle;
  ros::NodeHandle private_node("~");

  ros::CallbackQueue generic_queue;
  node_handle.setCallbackQueue(&generic_queue);

  ros::CallbackQueue read_state_queue;
  private_node.setCallbackQueue(&read_state_queue);

  LeobotRobotHW robot_hardware;
  robot_hardware.init(private_node);
  controller_manager::ControllerManager controller_manager(&robot_hardware, node_handle);

  ros::AsyncSpinner spinner(2, &generic_queue);
  spinner.start();

  struct timespec last_time;
  struct timespec current_time;
  clock_gettime(CLOCK_MONOTONIC, &last_time);

  int loop_rate;
  node_handle.param<int>("loop_rate", loop_rate, 100);

  double min_acceptable_rate;
  node_handle.param<double>("min_acceptable_loop_rate", min_acceptable_rate, 0.75 * loop_rate);

  ros::Duration desired_update_period = ros::Duration(1 / min_acceptable_rate);

  ros::Rate rate(loop_rate);
  while (ros::ok())
  {
    ros::Time timestamp = ros::Time::now();

    clock_gettime(CLOCK_MONOTONIC, &current_time);
    ros::Duration elapsed_time = ros::Duration(current_time.tv_sec - last_time.tv_sec +
                                               (current_time.tv_nsec - last_time.tv_nsec) / 1e+9);
    last_time = current_time;

    if (elapsed_time > desired_update_period)
    {
      ROS_WARN_STREAM_NAMED(node_name, "Cycle time exceeded error threshold by: " << (elapsed_time - desired_update_period) << ", cycle time: " << elapsed_time << ", desired_update_period: " << desired_update_period);
    }
    read_state_queue.clear();
    read_state_queue.callOne(ros::WallDuration(desired_update_period.toSec()));
    robot_hardware.read(timestamp, elapsed_time);
    controller_manager.update(ros::Time::now(), elapsed_time);
    // send message to firmware
    robot_hardware.write(timestamp, elapsed_time);
    rate.sleep();
  }

  spinner.stop();

  return 0;
}