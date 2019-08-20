#!/usr/bin/env bash

gzweb_home=${1:-/home/user/gzweb}
gzweb_port=${2:-8282}

pushd $gzweb_home
npm start -p $gzweb_port
popd
