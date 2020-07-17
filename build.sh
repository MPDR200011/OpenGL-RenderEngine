#!/bin/sh

RELEASE_TYPE="Release"

if [ $# == "0" ]; then
    RELEASE_TYPE="Release"
else
    RELEASE_TYPE=$1
fi

mkdir build/
cd build/
cmake -DCMAKE_BUILD_TYPE="$RELEASE_TYPE" ../
cp compile_commands.json -t ..
make
