FROM rosukraine/leobot-dev-web:latest

MAINTAINER "ROS Ukraine Community"

LABEL Description="This ROS Kinetic image for LeoBot development with Cloud 9 Web IDE and Java" Vendor="ROS Ukraine" Version="1.0"

USER user

RUN set -x && \
    \
    echo "Install ROS Java" && \
    sudo apt-get update && \
    sudo apt-get install -y ros-kinetic-rosjava && \
    \
    echo "Checkout and build special branch" && \
    pushd /home/user/workspace/leobot/base/src/leobot && \
    git fetch origin && \
    git checkout -b F_java_example origin/F_java_example && \
    /bin/bash -c 'cd /home/user/workspace/leobot/base; . /home/user/workspace/leobot/base/devel/setup.bash; rm -rf ./devel ./build; catkin_make' && \
    popd && \
    \
    echo "Clean up" && \
    sudo apt-get clean && \
    sudo rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /root/.ansible /root/.gitconfig /root/.cache

USER root

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]

EXPOSE 8080 8181 8282 8090 9090

CMD  ["/home/user/startup.sh"]
