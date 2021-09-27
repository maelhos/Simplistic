FROM randomdude/gcc-cross-x86_64-elf 
# GCC Compiling stuff

RUN apt-get update
RUN apt-get upgrade -y
# Update repo

RUN apt-get install nasm -y
# NASM is required for base of the Kernel

RUN apt-get install xorriso -y
RUN apt-get install grub-pc-bin -y
RUN apt-get install grub-common -y
# Grub and his dependencies for building the final ISO

VOLUME /root/env
WORKDIR /root/env