#/bin/bash --login
grep "model name" /proc/cpuinfo | uniq
head -n 1 /proc/meminfo
cpplint.py Lab02.cpp
g++ -O3 --std=c++17 -Wall -o Lab02.exe Lab02.cpp
echo "Switch runs"
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe switch 2000000000
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe switch 2000000000
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe switch 2000000000
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe switch 2000000000
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe switch 2000000000
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe switch 2000000000
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe switch 2000000000
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe switch 2000000000
echo "If runs"
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe if 2000000000
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe if 2000000000
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe if 2000000000
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe if 2000000000
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe if 2000000000
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe if 2000000000
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe if 2000000000
/usr/bin/time -f "Elapsed %E System %S User %U" ./Lab02.exe if 2000000000
