FROM rosukraine/leobot:latest

MAINTAINER "ROS Ukraine Community"

LABEL Description="This ROS Kinetic image for LeoBot development with Cloud 9 Web IDE" Vendor="ROS Ukraine" Version="1.0"

ARG leobot_aurora_branch

ENV leobot_aurora_branch ${leobot_aurora_branch:-"master"}

ENV leobot_aurora_script "https://raw.githubusercontent.com/ros-ukraine/aurora/$leobot_aurora_branch/bin/run-ansible.sh"

ENV LOCAL_USER_ID 1000

ENV MY_USERNAME user

ENV DISPLAY :1.0

ENV QT_X11_NO_MITSHM 1

USER user

COPY startup.sh /home/user/

RUN set -x && \
    \
    echo "Downloading one-liner" && \
    wget -O /tmp/oneliner "$( echo "$leobot_aurora_script" | sed 's/#/%23/g' )" && \
    chmod 755 /tmp/oneliner && \
    \
    echo "Installing IDEs and AWS CLI" && \
    /tmp/oneliner install_software --debug-branch $leobot_aurora_branch software=[cloud9,gzweb] && \
    \
    echo "Link models to gzweb folders" && \
    pushd /home/user/gzweb/http/client/assets && \
    ln -s /home/user/workspace/leobot/base/src/leobot/leobot_description ./leobot_description && \
    ln -s /home/user/workspace/leobot/base/src/leobot/leobot_gazebo ./leobot_gazebo && \
    popd && \
    \
    echo "Generating models for visualization" && \
    pushd /home/user/gzweb && \
    GAZEBO_MODEL_PATH=/home/user/workspace/leobot/base/src/leobot/leobot_gazebo/models npm run deploy --- -m local && \
    popd && \
    \
    echo "Clean up" && \
    sudo apt-get clean && \
    sudo rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /root/.ansible /root/.gitconfig /root/.cache

USER root

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]

EXPOSE 8080 8181 8282 8090 9090

CMD  ["/home/user/startup.sh"]
