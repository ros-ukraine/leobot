cmake_minimum_required(VERSION 2.8.3)
project(leobot_control)

find_package(catkin REQUIRED COMPONENTS)

catkin_package(
  CATKIN_DEPENDS joint_state_controller robot_localization ridgeback_control controller_manager teleop_twist_keyboard
)

install(FILES
  config/gazebo/leobot_control.yml
  launch/control.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)