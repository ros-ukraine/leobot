FROM shadowrobot/build-tools:xenial-kinetic-ide

MAINTAINER "ROS Ukraine Community"

LABEL Description="This ROS Kinetic image containes all dependencies for LeoBot development" Vendor="ROS Ukraine" Version="1.0"


RUN echo "Upgrading Gazebo 7 to latest release" && \
    apt-get update && \
    echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list && \
    wget http://packages.osrfoundation.org/gazebo.key -O - | apt-key add - && \
    apt-get update && \
    apt-get remove -y gazebo7 && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y gazebo7 && \

    echo "Loading gazebo models" && \
    /home/$MY_USERNAME/sr-build-tools/docker/utils/load_gazebo_models.sh && \
    mv /root/.gazebo /home/$MY_USERNAME && \
    chown -R $MY_USERNAME:$MY_USERNAME /home/$MY_USERNAME/.gazebo && \

    echo "Removing cache" && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /home/$MY_USERNAME/.ansible /home/$MY_USERNAME/.gitconfig

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]

CMD ["/usr/bin/terminator"]