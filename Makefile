all: lab1


lab1:
		gcc lab1.c -o lab1 -lm

omp:
		gcc -O3 -Wall -Werror lab1.c -fopenmp -o lab3_omp -lm

omp_o2:
		gcc -O2 -Wall -Werror lab1.c -fopenmp -o lab3_omp_o2 -lm

omp_o1:
		gcc -O1 -Wall -Werror lab1.c -fopenmp -o lab3_omp_o1 -lm

omp_o0:
		gcc -O0 -Wall -Werror lab1.c -fopenmp -o lab3_omp_o0 -lm

omp_test:
		./lab3_omp 100 10 test_omp

omp_clean:
		rm -f lab3_omp
		rm -f lab3_omp_o0
		rm -f lab3_omp_o1
		rm -f lab3_omp_o2
		rm -f test_omp_ans.txt

gcc-seq:
		gcc -O3 -Wall -Werror lab1.c -o lab1-seq -lm
		gcc -O3 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=1 lab1.c -o lab1-par-1 -lm
		gcc -O3 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=2 lab1.c -o lab1-par-2 -lm
		gcc -O3 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=3 lab1.c -o lab1-par-3 -lm
		gcc -O3 -Wall -Werror -floop-parallelize-all -ftree-parallelize-loops=10 lab1.c -o lab1-par-10 -lm


clean:
		rm -f lab1
		rm -f lab1-par-1
		rm -f lab1-par-2
		rm -f lab1-par-3
		rm -f lab1-par-10
		rm -f lab1-seq
		rm -f lab1-tcc-3
		rm -f lab1-pcc-3
