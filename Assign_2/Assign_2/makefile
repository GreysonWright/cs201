OBJS = bstrees.o queue.o sll.o bst.o rbt.o vbst.o scanner.o string.o
OPTS = -Wall -g -std=c99 -Wextra

bstrees : $(OBJS)
		gcc $(OPTS) $(OBJS) -o bstrees -lm

bstrees.o : bstrees.c
		gcc $(OPTS) -c bstrees.c

queue.o : queue.c queue.h
		gcc $(OPTS) -c queue.c
		
sll.o : sll.c sll.h
		gcc $(OPTS) -c sll.c

scanner.o : scanner.c scanner.h
		gcc $(OPTS) -c scanner.c

string.o : string.c string.h
		gcc $(OPTS) -c string.c

bst.o : bst.c bst.h
		gcc $(OPTS) -c bst.c

rbt.o : rbt.c rbt.h
		gcc $(OPTS) -c rbt.c

vbst.o : vbst.c vbst.h
		gcc $(OPTS) -c vbst.c

clean :
		rm -f $(OBJS) bstrees

test :	./bstrees
		./bstrees -r corpus commands
		
