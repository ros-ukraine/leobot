FROM shadowrobot/build-tools:xenial-kinetic-ide

MAINTAINER "ROS Ukraine Community"

LABEL Description="This ROS Kinetic image containes all dependencies for LeoBot with IDEs" Vendor="ROS Ukraine" Version="1.0"

ENV remote_deploy_script="https://raw.githubusercontent.com/shadow-robot/sr-build-tools/$toolset_branch/ansible/deploy.sh"

RUN set -x && \

    echo "Upgrading Gazebo 7 to latest release" && \
    apt-get update && \
    echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list && \
    wget http://packages.osrfoundation.org/gazebo.key -O - | apt-key add - && \
    apt-get update && \
    apt-get remove -y gazebo7 && \
    apt-get install -y gazebo7 && \

    echo "Loading gazebo models" && \
    /home/$MY_USERNAME/sr-build-tools/docker/utils/load_gazebo_models.sh -u $MY_USERNAME && \
    chown -R $MY_USERNAME:$MY_USERNAME /home/$MY_USERNAME/.gazebo && \

    echo "Backing up .bashrc" && \
    cp /home/$MY_USERNAME/.bashrc /tmp && \

    echo "Running one-liner" && \
    wget -O /tmp/oneliner "$( echo "$remote_deploy_script" | sed 's/#/%23/g' )" && \
    chmod 755 /tmp/oneliner && \
    gosu $MY_USERNAME /tmp/oneliner -o ros-ukraine -r leobot -b kinetic-devel -v kinetic && \

    echo "Restoring .bashrc" && \
    cp /tmp/.bashrc /home/$MY_USERNAME && \

    echo "Removing workspace folder" && \
    rm -rf /home/$MY_USERNAME/workspace/leobot && \

    echo "Removing cache" && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /home/$MY_USERNAME/.ansible /home/$MY_USERNAME/.gitconfig

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]

CMD ["/usr/bin/terminator"]
