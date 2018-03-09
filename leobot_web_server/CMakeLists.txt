cmake_minimum_required(VERSION 2.8.3)
project(leobot_web_server)

find_package(catkin REQUIRED)

catkin_package()

add_custom_target(install_nodejs ALL
  COMMAND npm i
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  COMMENT "Installing NodeJS dependencies"
  VERBATIM
)

add_custom_target(copy_roslib_js ALL
  COMMAND cp -u "node_modules/roslib/build/roslib.min.js" "web_content/js"
  DEPENDS install_nodejs
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  COMMENT "Copying roslib to web folder"
  VERBATIM
)

install(DIRECTORY
  scripts
  web_content
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
