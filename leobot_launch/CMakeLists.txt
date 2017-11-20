cmake_minimum_required(VERSION 2.8.3)
project(leobot_launch)

find_package(catkin REQUIRED)

catkin_package(
  CATKIN_DEPENDS leobot_gazebo leobot_description
)

install(FILES
  launch/display.launch
  launch/simulation.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
