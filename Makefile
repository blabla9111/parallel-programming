all: lab1


lab1:
		gcc lab1.c -o lab1 -lm


gcc-seq:
		gcc -O3 -Wall -Werror lab1.c -o lab1-seq -lm
		gcc -O3 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=1 lab1.c -o lab1-par-1 -lm
		gcc -O3 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=2 lab1.c -o lab1-par-2 -lm
		gcc -O3 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=3 lab1.c -o lab1-par-3 -lm
		gcc -O3 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=10 lab1.c -o lab1-par-10 -lm
		
tcc-seq:
		tcc -O3 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=3 lab1.c -o lab1-tcc-3 -lm
		
pcc-seq:
		pcc -O3 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=3 lab1.c -o lab1-pcc-3 -lm

start-gcc:
		./lab1-seq 10000 10 seq
		./lab1-par-1 10000 10 par1
		./lab1-par-2 10000 10 par2
		./lab1-par-3 10000 10 par3
		./lab1-par-10 10000 10 par10
                
test:
		./lab1 10 10


clean:
		rm -f lab1
		rm -f lab1-par-1
		rm -f lab1-par-2
		rm -f lab1-par-3
		rm -f lab1-par-10
		rm -f lab1-seq
		rm -f lab1-tcc-3
		rm -f lab1-pcc-3
