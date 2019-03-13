cmake_minimum_required(VERSION 2.8.3)
project(leobot_launch)

find_package(catkin REQUIRED)

catkin_package(
  CATKIN_DEPENDS leobot_gazebo leobot_hardware leobot_description
)

install(FILES
  launch/gmapping.launch
  launch/hardware.launch
  launch/navigation.launch
  launch/rviz.launch
  launch/simulation.launch
  launch/teleop.launch
  launch/view_urdf.launch
  launch/web_server.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
