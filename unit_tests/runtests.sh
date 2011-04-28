#!/bin/bash
set -e
echo "building unit tests"
gcc -g -std=c99 -pedantic -I.. -o ./heaptest ./heaptest.c ../heap.c ../array.c
gcc -g -std=c99 -pedantic -D_POSIX_C_SOURCE=199309 -I.. -lrt -lpthread -o ./timertest ./timertest.c ../timer.c ../heap.c ../array.c
echo "running heap test"
./heaptest
echo "running timer test"
./timertest
