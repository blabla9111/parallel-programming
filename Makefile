obj-m += lab1.o

all: lab1

lab1:
		gcc lab1.c -o lab1 -lm

test:
		./lab1

clean:
		rm -f lab1
