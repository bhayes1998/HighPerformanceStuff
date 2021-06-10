#/bin/bash --login
grep "model name" /proc/cpuinfo | uniq
head -n 1 /proc/meminfo

g++ -g -O2 --std=c++17 -Wall -o Lab03-good.exe Lab03-good.cpp
g++ -g -O2 --std=c++17 -Wall -o Lab03-bad.exe Lab03-bad.cpp

perf stat -o Lab03-good.perfstat -d -d -d ./Lab03-good
perf stat -o Lab03-bad.perfstat -d -d -d ./Lab03-bad
