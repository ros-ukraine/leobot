#!/bin/bash

sudo apt-get update

cd ~/workspace/leobot/base

rosdep install --from-paths src --ignore-src --rosdistro kinetic -y

cd ~/workspace/leobot/base/src/leobot/leobot_web_server
npm i
