#!/bin/bash -l

grep "model name" /proc/cpuinfo | uniq
grep MemTotal /proc/meminfo

g++ -O3 -g -Wall -std=c++17 -o  ackermann ackermann.cpp
ulimit -s unlimited 

perf stat -o baseline.perfstat -d -d -d ./ackermann 16 
perf stat -o baseline.perfstat --append -d -d -d ./ackermann 16 
perf stat -o baseline.perfstat --append -d -d -d ./ackermann 16 
perf stat -o baseline.perfstat --append -d -d -d ./ackermann 16 
perf stat -o baseline.perfstat --append -d -d -d ./ackermann 16 
perf stat -o baseline.perfstat --append -d -d -d ./ackermann 16 

g++ -O3 -g -Wall -std=c++17 -fprofile-generate -o ackermann_pgo ackermann.cpp
./ackermann_pgo 9 
./ackermann_pgo 11
./ackermann_pgo 13
./ackermann_pgo 15 

g++ -O3 -g -Wall -std=c++17 -fprofile-use -o ackermann_pgo ackermann.cpp

perf stat -o post.perfstat -d -d -d ./ackermann_pgo 16
perf stat -o post.perfstat --append -d -d -d ./ackermann_pgo 16
perf stat -o post.perfstat --append -d -d -d ./ackermann_pgo 16
perf stat -o post.perfstat --append -d -d -d ./ackermann_pgo 16
perf stat -o post.perfstat --append -d -d -d ./ackermann_pgo 16
perf stat -o post.perfstat --append -d -d -d ./ackermann_pgo 16


