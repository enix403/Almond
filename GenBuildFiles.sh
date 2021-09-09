#!/usr/bin/env bash

# You can add extra arguments which will be passed to cmake
# Example: Run `./GenBuildFiles Release -G Ninja` to use the ninja build system instead of the default 

# Also you can choose which compiler to use using the `CC` and `CXX` environment variables
# Example: Run `CC=/usr/bin/clang CXX=/usr/bin/clang++ ./GenBuildFiles Release -G Ninja` to use clang instead of default compiler 

function GenBuildFiles_Debug() {
    mkdir -p build/debug
    echo "------------ Generating build files for Debug build mode ------------"
    exec env cmake -B build/debug -DCMAKE_BUILD_TYPE=Debug "${@}" -S .   
}

function GenBuildFiles_Release() {
    mkdir -p build/release
    echo "------------ Generating build files for Release build mode ------------"
    cmake -B build/release -DCMAKE_BUILD_TYPE=Release "${@}" -S .
}

if [[ -z "$1" ]]
then
    echo "Please specify build mode (\`Debug\` or \`Release\`)"
    echo "Example: ./GenBuildFiles Release"
elif [[ "$1" == "Debug" ]]
then
    GenBuildFiles_Debug "${@:2}"
elif [[ "$1" == "Release" ]]
then
    GenBuildFiles_Release "${@:2}"
else
    echo "Invalid build mode: '$1'"
    echo "Allowed modes are: 'Release', 'Debug'"
    exit 1
fi

