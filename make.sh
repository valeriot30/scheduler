gcc -c -g task.c
gcc -c -g queues.c
gcc -c -g queue.c
gcc -c -g main.c
gcc main.o queue.o task.o queues.o -o scheduler
./scheduler
