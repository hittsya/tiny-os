#!/usr/bin/env bash

IMAGE_NAME="toolchain/tiny-toolchain"

if [[ "$(docker images -q $IMAGE_NAME 2> /dev/null)" == "" || $FORCE_BUILD == "1" ]]; then
    echo "Building the Docker image: $IMAGE_NAME"
    docker build -t $IMAGE_NAME -f toolchain/Dockerfile .
else
    echo "Skipping build of the $IMAGE_NAME docker image"
fi

docker run -it --rm -v .:/home/builder/src $IMAGE_NAME make
make run
