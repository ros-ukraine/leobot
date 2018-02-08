cmake_minimum_required(VERSION 2.8.3)
project(leobot_web_server)

find_package(catkin REQUIRED)

add_custom_target(install_nodejs ALL
  COMMAND npm install
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  COMMENT "Installing NodeJS dependencies"
  VERBATIM
)
