#!/bin/bash

# Update all system packages within docker container to prevent the issue
# with rosdep failing to find the nodejs and npm packages
sudo apt-get update

cd ~/workspace/leobot/base

# Install the rosdep packages
rosdep install --from-paths src --ignore-src --rosdistro kinetic -y

# Install the NPM dependencies
cd ~/workspace/leobot/base/src/leobot/leobot_web_server
npm i
