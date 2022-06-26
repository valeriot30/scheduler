#!/bin/bash

gcc -g -c task.c
gcc -g -c queue.c
gcc -g -c queues.c
gcc -g -c main.c
gcc main.o queue.o task.o queues.o -o scheduler

./scheduler