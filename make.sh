#!/bin/bash

clean () {
    echo "Cleaning"
    rm -f bin/*
    rm -f lib/*
    rm -rf build
}

build () {
    clean
    mkdir -p build ; cd build ; cmake .. -DCMAKE_BUILD_TYPE=$1 $2 && cmake --build . -j4 ; cd ..
}

case $1 in

    "Test")
        echo "Building test"
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
