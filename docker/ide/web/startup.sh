#!/usr/bin/env bash

nohup Xvfb :1 -screen 0 1024x768x16 &> /home/user/gzweb/xvfb.log &

pushd /home/user/c9sdk
project_home=/home/user/workspace/leobot/base/src/leobot/
node ./server.js --listen 0.0.0.0 --port 8181 -w $project_home -a :
popd
