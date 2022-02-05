#!/bin/sh

if [ ! -d "./build" ]
then
  mkdir build
fi

cd build

cmake .. && cmake --build .

if [ $# == 1 ]
then
  if [ $1 == "test" ]
  then
    ctest
  fi
fi
