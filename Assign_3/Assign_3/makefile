OBJS = dijkstra.o integer.o sll.o scanner.o queue.o darray.o binomial.o vertex.o
OPTS = -Wall -g -std=c99 -Wextra

dijkstra : $(OBJS)
		gcc $(OPTS) $(OBJS) -o dijkstra -lm

dijkstra.o : dijkstra.c
		gcc $(OPTS) -c dijkstra.c

integer.o : integer.c integer.h
		gcc $(OPTS) -c integer.c

darray.o : darray.c darray.h
		gcc $(OPTS) -c darray.c

binomial.o : binomial.c binomial.h
		gcc $(OPTS) -c binomial.c

vertex.o : vertex.c vertex.h
		gcc $(OPTS) -c vertex.c

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
		rm -f $(OBJS) dijkstra

test :	./dijkstra
		./dijkstra data
		
