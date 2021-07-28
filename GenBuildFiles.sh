#!/usr/bin/env bash

function GenBuildFiles_Debug() {
    mkdir -p build/debug
    echo "------------ Generating build files for Debug build mode ------------"
    cmake -B build/debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -S .   
}

function GenBuildFiles_Release() {
    mkdir -p build/release
    echo "------------ Generating build files for Release build mode ------------"
    cmake -B build/release -G Ninja -DCMAKE_BUILD_TYPE=Release -S .   
}

if [[ -z "$1" ]]
then
    GenBuildFiles_Debug
    echo
    GenBuildFiles_Release
elif [[ "$1" == "Debug" ]]
then
    GenBuildFiles_Debug
elif [[ "$1" == "Release" ]]
then
    GenBuildFiles_Release
else
    echo "Invalid build mode: '$1'"
    echo "Allowed modes are: 'Release', 'Debug'"
    exit 1
fi

