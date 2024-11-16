FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages
RUN apt update && apt install -y \
        nasm gcc make curl tar \
        build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo \
        qemu-system-i386 xorriso grub-pc-bin grub-common \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m builder
RUN echo "dockeruser ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

ENV HOME=/home/builder
RUN echo 'export PS1="(tiny-toolchain) \u@\h:\w\$ "' >> $HOME/.bashrc
ENV TERM=xterm-256color
ENV COMPILE="make -n"

ENV PREFIX="/usr/local/i386elfgcc"
ENV TARGET=i386-elf
ENV PATH="$PREFIX/bin:$PATH"

# Build binutils
RUN mkdir /tmp/src && cd /tmp/src &&\
    curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.gz &&\
    tar xf binutils-2.42.tar.gz &&\
    mkdir binutils-build && cd binutils-build &&\
        ../binutils-2.42/configure \
        --target=$TARGET \
        --enable-interwork \
        --enable-multilib \
        --disable-nls \
        --disable-werror \
        --prefix=$PREFIX &&\
    make &&\
    make install &&\
    cd / && rm -rf /tmp/src

# Build GCC
RUN curl -O https://ftp.gnu.org/gnu/gcc/gcc-12.1.0/gcc-12.1.0.tar.gz &&\
    tar xf gcc-12.1.0.tar.gz &&\
    cd gcc-12.1.0 &&\
    ./contrib/download_prerequisites &&\
    mkdir gcc-build && cd gcc-build &&\
        ../configure \
        --target=$TARGET \
        --prefix="$PREFIX" \
        --disable-nls \
        --disable-libssp \
        --enable-language=c,c++ \
        --without-headers &&\
    make all-gcc -j$(nproc) &&\
    make all-target-libgcc -j$(nproc) &&\
    make install-gcc -j$(nproc) &&\
    make install-target-libgcc -j$(nproc) &&\
    cd / && rm -rf gcc-12.1.0 gcc-12.1.0.tar.gz

ENV PATH="$PATH:/usr/local/i386elfgcc/bin"

# Set up environment for x86_64-elf cross-compiling
ENV PREFIX="/usr/local/x86_64elfgcc"
ENV TARGET=x86_64-elf
ENV PATH="$PREFIX/bin:$PATH"

# Build and install binutils
RUN mkdir /tmp/src && cd /tmp/src &&\
    curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.gz &&\
    tar xf binutils-2.42.tar.gz &&\
    mkdir binutils-build && cd binutils-build &&\
        ../binutils-2.42/configure \
        --target=$TARGET \
        --enable-interwork \
        --enable-multilib \
        --disable-nls \
        --disable-werror \
        --prefix=$PREFIX &&\
    make -j$(nproc) &&\
    make install &&\
    cd / && rm -rf /tmp/src

# Build and install GCC
RUN curl -O https://ftp.gnu.org/gnu/gcc/gcc-12.1.0/gcc-12.1.0.tar.gz &&\
    tar xf gcc-12.1.0.tar.gz &&\
    cd gcc-12.1.0 &&\
    ./contrib/download_prerequisites &&\
    mkdir gcc-build && cd gcc-build &&\
        ../configure \
        --target=$TARGET \
        --prefix="$PREFIX" \
        --disable-nls \
        --disable-libssp \
        --enable-language=c,c++ \
        --without-headers &&\
    make all-gcc -j$(nproc) &&\
    make all-target-libgcc -j$(nproc) &&\
    make install-gcc -j$(nproc) &&\
    make install-target-libgcc -j$(nproc) &&\
    cd / && rm -rf /tmp/src /gcc-12.1.0 /gcc-12.1.0.tar.gz

ENV PATH="$PATH:/usr/local/i386elfgcc/bin"

USER builder
WORKDIR $HOME/src

# Set default command
CMD ["/bin/bash"]
