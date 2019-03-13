cmake_minimum_required(VERSION 2.8.3)
project(leobot_control)

find_package(catkin REQUIRED COMPONENTS)

catkin_package(
  CATKIN_DEPENDS 
    joint_state_controller 
    robot_localization 
    ridgeback_control 
    controller_manager 
    teleop_twist_keyboard 
    velocity_controllers
    effort_controllers
)

install(FILES
  config/common/joystick.yml
  config/common/keyboard.yml
  config/common/state_controller.yml
  config/common/twist_mux.yml
  config/common/velocity_controllers.yml
  config/gazebo/head_controller.yml
  config/gazebo/mecanum_controller.yml
  config/hardware/head_controller.yml
  config/hardware/mecanum_controller.yml
  launch/control.launch
  launch/teleop.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)