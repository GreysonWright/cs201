OBJS = main.o stack.o queue.o sll.o dll.o integer.o
OPTS = -Wall -g -std=c99

assign_0 : $(OBJS)
		gcc $(OPTS) $(OBJS) -o assign_0 -lm

main.o : main.c
		gcc $(OPTS) -c main.c

stack.o : stack.c stack.h
		gcc $(OPTS) -c stack.c

queue.o : queue.c queue.h
		gcc $(OPTS) -c queue.c
		
sll.o : sll.c sll.h
		gcc $(OPTS) -c sll.c

dll.o : dll.c dll.h
		gcc $(OPTS) -c dll.c

integer.o : integer.c integer.h
		gcc $(OPTS) -c integer.c		

clean :
		rm -f $(OBJS) main

test :
		./assign_0
		
