#!/usr/bin/env bash

function GenBuildFiles_Debug() {
    mkdir -p build/debug
    echo "------------ Generating build files for Debug build mode ------------"
    cmake -B build/debug -DCMAKE_BUILD_TYPE=Debug "${@}" -S .   
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

