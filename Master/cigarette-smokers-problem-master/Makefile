all:		smokersproblem

smokersproblem:	smokersproblem.o
	gcc smokersproblem.o -o smokersproblem -pthread

smokersproblem.o: smokersproblem.c
	gcc -c smokersproblem.c
run:	smokersproblem
	@./smokersproblem

clean:
	@rm smokersproblem.o smokersproblem
