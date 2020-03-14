#!/bin/bash

clean () {
    rm -f bin/*
    rm -f lib/*
    rm -rf build
}

build () {
    clean
    mkdir -p build ; cd build
    cmake .. -DCMAKE_BUILD_TYPE=$1 $2 && cmake --build . -j4
    res=$?
    if [ $res -ne 0 ]; then
        exit $res
    fi
    cd ..
}

case $1 in

    "Test")
        build Debug -DBUILD_TEST=True
        make -C build coverage
        ;;

    "clean")
        clean
        ;;

    *)
        build $1
        ;;
esac
