cmake_minimum_required(VERSION 2.8.3)
project(leobot_gazebo)

find_package(catkin REQUIRED)

catkin_package(
  CATKIN_DEPENDS gazebo_ros gazebo_ros_control hector_gazebo_plugins ridgeback_gazebo_plugins leobot_description
)

install(FILES
  launch/gazebo.launch
  worlds/office.world
  scripts/launch_gzweb.sh
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
