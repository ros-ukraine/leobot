cmake_minimum_required(VERSION 2.8.3)
project(leobot_control)

find_package(catkin REQUIRED)

catkin_package(
  CATKIN_DEPENDS effort_controllers joint_state_controller controller_manager diff_drive_controller teleop_twist_keyboard
)

install(FILES
  config/gazebo/leobot_control.yml
  launch/control.launch
  launch/teleop.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)