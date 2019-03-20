#!/usr/bin/env bash

script_file=$(readlink -f "$0")
script_path=$(dirname "$script_file")

firmware_messages=$script_path/../firmware/STM32F767_Firmware/Libs/rosserial/

messages_directory=/tmp/messages
rm -rf $messages_directory

rosrun rosserial_mbed make_libraries.py $messages_directory

rm -rf $firmware_messages/rosserial_msgs
rm -rf $firmware_messages/std_msgs
rm -rf $firmware_messages/leobot_msgs

mv $messages_directory/ros_lib/rosserial_msgs $firmware_messages
mv $messages_directory/ros_lib/std_msgs $firmware_messages
mv $messages_directory/ros_lib/leobot_msgs $firmware_messages

rm -rf $messages_directory