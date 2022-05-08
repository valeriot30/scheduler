#!/bin/bash

gcc -g -c multilevel_queue.c
gcc -g -c task.c
gcc -g -c scheduler.c
gcc -g -c queue.c
gcc -g -c queues.c
gcc scheduler.o multilevel_queue.o queue.o task.o queues.o -o scheduler

./scheduler