FROM rosukraine/leobot:latest

MAINTAINER "ROS Ukraine Community"

LABEL Description="This ROS Kinetic image for LeoBot development with IDEs for NVidia Graphic Card" Vendor="ROS Ukraine" Version="1.0"

LABEL com.nvidia.volumes.needed="nvidia_driver"

ENV PATH /usr/local/nvidia/bin:${PATH}

ENV LD_LIBRARY_PATH /usr/local/nvidia/lib:/usr/local/nvidia/lib64:${LD_LIBRARY_PATH}

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]

CMD ["/usr/bin/terminator"]