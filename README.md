# round-robin-scheduling

This program utilized the Round Robin scheduling algorithm to schedule processes to be executed by a processor. 
Each process enter a queue and executes in a FIFO order. After a certain, previously specified time, its execution stops, it either aborts if its time is finished and lets the following process start or is put back in the queue to continue processing.

This program should be given a txt file with the name of the processes that needs execution, the time slot that it will enter the queue and the needed time for its execution.

The given input file will have the watching time slots in the first line, then in the successive lines it will contain the name of the process, time it enters the queue, and the needed time for execution respectively.

The output is the scheduling of the processes, showing when does each process abort and when does the processor is idle (no processes in the queue).
Each process enters the queue whenever its execution time comes. Each process will be granted 1 time slot on execution, if its execution time finishes it will abort, else it will be sent again to the queue and its execution time will be subtracted by 1.
