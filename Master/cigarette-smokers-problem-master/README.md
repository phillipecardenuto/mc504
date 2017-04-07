# The Cigarette Smokers' Problem
## POSIX Threads and Semaphores

To build and run the program run the following commands:

	gcc -c smokersproblem.c
	gcc smokersproblem.o -o smokersproblem -pthread
	./smokersproblem

Or use the included Makefile to build and run the program using the following:

	make run

The program will output what items the agents are setting on the table
and what items the smokers are waiting for. There are also messages indicating
when the smoker is making one of their cigarettes and when they are actively
smoking.
