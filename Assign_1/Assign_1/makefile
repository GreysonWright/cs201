OBJS = sqsort.o stack.o queue.o sll.o dll.o scanner.o integer.o real.o string.o comparator.o
OPTS = -Wall -g -std=c99 -Wextra

sqsort : $(OBJS)
		gcc $(OPTS) $(OBJS) -o sqsort -lm

sqsort.o : sqsort.c
		gcc $(OPTS) -c sqsort.c

stack.o : stack.c stack.h
		gcc $(OPTS) -c stack.c

queue.o : queue.c queue.h
		gcc $(OPTS) -c queue.c
		
sll.o : sll.c sll.h
		gcc $(OPTS) -c sll.c

dll.o : dll.c dll.h
		gcc $(OPTS) -c dll.c

scanner.o : scanner.c scanner.h
		gcc $(OPTS) -c scanner.c

integer.o : integer.c integer.h
		gcc $(OPTS) -c integer.c		

real.o : real.c real.h
		gcc $(OPTS) -c real.c

string.o : string.c string.h
		gcc $(OPTS) -c string.c

comparator.o : comparator.c comparator.h
		gcc $(OPTS) -c comparator.c

clean :
		rm -f $(OBJS) sqsort

test :	./sqsort
		./sqsort -d mytestfile
		
