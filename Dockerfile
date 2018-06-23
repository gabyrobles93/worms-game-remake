# Pull de imagen de oracle linux
FROM oraclelinux
USER root
RUN echo "root:root" | chpasswd
# Install dependencies
RUN yum clean all
RUN yum install -y git
RUN yum install -y libsdl2-dev
RUN yum install -y libsdl2-image-dev
RUN yum install -y libsdl2-ttf-dev
RUN yum install -y libsdl2-mixer-dev
RUN yum install -y qt5-default
RUN yum install -y cmake
RUN yum install -y xorg-x11-xauth xterm
RUN yum install -y openssh
RUN yum install -y openssh-server
RUN yum install -y sshd-keygen
RUN /usr/sbin/sshd -D &
RUN yum install -y xauth xdpyinfo