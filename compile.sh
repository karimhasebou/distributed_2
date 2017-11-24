#!/bin/bash


mv cmake1.txt CMakeLists.txt
cmake .
make 
mv CMakeLists.txt cmake1.txt

mv cmake2.txt CMakeLists.txt
cmake .
make
mv CMakeLists.txt cmake2.txt



