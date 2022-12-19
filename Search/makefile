# pre-processing only
#main.i: main.c
#	cpp main.c > main.i



# compilation only
#main.s: main.i
#	gcc -S main.i


# assembling only
#main.o: main.s
#	as -o main.o main.s

# all preprocessing, compiling, assembling.
#main.o: main.c
#	gcc -c main.c
#node.o: node.c
#	gcc -c node.c

#searchDisplay.o: searchDisplay.c
#	gcc -c searchDisplay.c

all: node.o main.o 
	gcc -o main node.o main.o
	./main