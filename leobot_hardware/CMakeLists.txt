cmake_minimum_required(VERSION 2.8.3)
project(leobot_hardware)

add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
    leobot_msgs)

catkin_package(
  CATKIN_DEPENDS leobot_msgs
)
