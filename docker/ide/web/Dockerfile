FROM rosukraine/leobot:latest

MAINTAINER "ROS Ukraine Community"
ln -s /home/user/workspace/leobot/base/src/leobot/leobot_gazebo /home/user/gzweb/http/client/assets/leobot_gazebo
LABEL Description="This ROS Kinetic image for LeoBot development with Cloud 9 Web IDE" Vendor="ROS Ukraine" Version="1.0"

ARG leobot_aurora_branch

ENV leobot_aurora_branch ${leobot_aurora_branch:-"master"}

ENV leobot_aurora_script "https://raw.githubusercontent.com/ros-ukraine/aurora/$leobot_aurora_branch/bin/run-ansible.sh"

ENV LOCAL_USER_ID 1000

ENV MY_USERNAME user

USER user

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
    echo "Clean up" && \
    sudo apt-get clean && \
    sudo rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /root/.ansible /root/.gitconfig /root/.cache

USER root

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]

EXPOSE 8181

EXPOSE 8282

CMD node /home/user/c9sdk/server.js --listen 0.0.0.0 --port 8181 -w /home/user/workspace -a :
