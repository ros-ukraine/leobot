#include "leobot_hardware/robot_hardware.h"
#include <controller_manager/controller_manager.h>
#include <hardware_interface/actuator_state_interface.h>
#include <ros/callback_queue.h>

using leobot_hardware::LeobotRobotHW;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "leobot_hardware_node");
  ros::NodeHandle node_handle;
  ros::CallbackQueue queue;
  node_handle.setCallbackQueue(&queue);

  LeobotRobotHW robot;
  robot.init(node_handle);
  controller_manager::ControllerManager controller_manager(&robot, node_handle);

  ros::AsyncSpinner spinner(1, &queue);
  spinner.start();

  ros::Time ts = ros::Time::now();

  int loop_rate;
  node_handle.param<int>("loop_rate", loop_rate, 100);

  ros::Rate rate(loop_rate);
  while (ros::ok())
  {
     ros::Duration d = ros::Time::now() - ts;
     ts = ros::Time::now();
    //  queue.clear();
    //  queue.callOne();
    //  queue.callAvailable();
    // TODO: In read function subscribe to topic and read the most recent one
    // set queue size for subscriber to 1 not to hold old messages
    // in callback unsubscribe from messages 
     robot.read(ts, d);
     controller_manager.update(ts, d);
     // send message to firmware
     robot.write(ts, d);
     rate.sleep();
  }

  spinner.stop();

  return 0;
}