cmake_minimum_required(VERSION 2.8.3)
project(leobot_launch)

find_package(catkin REQUIRED)

catkin_package(
  CATKIN_DEPENDS leobot_gazebo leobot_description
)

install(FILES
  launch/view_urdf.launch
  launch/simulation.launch
  launch/navigation.launch
  launch/rviz.launch
  launch/teleop.launch
  launch/web_server.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
