FROM rosukraine/leobot:latest

MAINTAINER "ROS Ukraine Community"

LABEL Description="This ROS Kinetic image for LeoBot development with IDEs for Intel Graphic Card" Vendor="ROS Ukraine" Version="1.0"

RUN set -x && \

    echo "Installing video drivers for user" && \
    apt-get update && \
    apt-get -y install libgl1-mesa-glx libgl1-mesa-dri && \
    usermod -a -G video user && \

    echo "Removing cache" && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /home/$MY_USERNAME/.ansible /home/$MY_USERNAME/.gitconfig

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]

CMD ["/usr/bin/terminator"]