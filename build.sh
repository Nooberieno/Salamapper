#!/bin/bash

set -e

CC=clang++

if [ "$(id -u)" != "0" ];then
    echo "This script needs elevated priviliges, please rerun with sudo or elevated priviliges"
    exit 1
fi

if ! $CC -v &>/dev/null; then
    echo "clang is not installed, please specify another C++ compiler or install clang"
    exit 1
fi

echo "clang availlable, starting compilation..."

mkdir -p /usr/include/salamapper

cp *.hpp /usr/include/salamapper/
cp salamapper.h /usr/include/salamapper/

$CC -fPIC -c *.cpp
$CC -shared *.o -o libsalamapper.so

if [ -d "/usr/lib64" ];then
    mv libsalamapper.so /usr/lib64/
else
    mv libsalamapper.so /usr/lib/
fi

echo "Installation succesful, cleaning up..."

rm *.o

echo "Installation completed succesfully"