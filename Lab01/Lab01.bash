#!/bin/bash
grep "model name" /proc/cpuinfo | uniq
head -n 1 /proc/meminfo
python2.7 cpplint.py Lab01.cpp
g++ -O3 --std=c++17 -Wall -o Lab01.exe Lab01.cpp
/usr/bin/time ./Lab01.exe
/usr/bin/time ./Lab01.exe
/usr/bin/time ./Lab01.exe
/usr/bin/time ./Lab01.exe
/usr/bin/time ./Lab01.exe 
