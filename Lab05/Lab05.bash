#!/bin/bash -l

grep "model name" /proc/cpuinfo | uniq
grep MemTotal /proc/meminfo

g++ -g -O3 -std=c++17 -Wall -o Lab05 Lab05.cpp

echo "Initial" 
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05
 
g++ -g -O3 -std=c++17 -Wall -fopenmp -o Lab05_omp Lab05.cpp

echo "1 thread"
export OMP_NUM_THREADS=1
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp

echo "2 threads"
export OMP_NUM_THREADS=2
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp

echo "3 threads"
export OMP_NUM_THREADS=3
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp

echo "4 threads"
export OMP_NUM_THREADS=4
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp

echo "5 threads"
export OMP_NUM_THREADS=5
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp

echo "6 threads"
export OMP_NUM_THREADS=6
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp

echo "7 threads"
export OMP_NUM_THREADS=7
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp

echo "8 threads"
export OMP_NUM_THREADS=8
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab05_omp

