cmake_minimum_required(VERSION 2.8.3)
project(leobot_description)

find_package(catkin REQUIRED)

catkin_package()

install(FILES
  launch/display.launch
  urdf/common.urdf.xacro
  urdf/materials.urdf.xacro
  urdf/wheels.urdf.xacro
  urdf/sensors/hokuyo.urdf.xacro
  robot/robot.urdf.xacro
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
