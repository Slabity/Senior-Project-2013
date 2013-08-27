#!/bin/bash

BASEDIR=$(dirname $0)

echo "Location: ${BASEDIR}"

echo "Removing ${BASEDIR}/bin"
rm -r $BASEDIR/bin/
echo "Removing ${BASEDIR}/CMakeFiles"
rm -r $BASEDIR/CMakeFiles/
echo "Removing ${BASEDIR}/CMakeCache.txt"
rm $BASEDIR/CMakeCache.txt
echo "Removing ${BASEDIR}/Makefile"
rm $BASEDIR/Makefile
echo "Removing ${BASEDIR}/cmake_install.cmake"
rm $BASEDIR/cmake_install.cmake
