//
// Created by dinara on 11.03.23.
//
#include "lab1.h"

int main(int args, char *argv[]) {
    int i, N1, N2, A;
    struct timeval T1, T2;
    long delta_ms;
    N1 = atoi(argv[1]);
    N2 = N1 / 2;
    A = atoi(argv[2]);
    if (N1 ==0 || A==0){
        printf("One or both args  = 0");
        return -1;
    }
    gettimeofday(&T1, NULL);
    double M1[N1], M2[N2];
    printf("Hello!");
    for (i = 0; i < 100; i++) {
        srand(i);
        printf("i = %d", i);
        int seed = i;
        printf("\n\nStarted to fill M1 ...\n");
        generate_array(N1, M1, 1, A, seed);

        printf("\n\nfunc cosh(num) - 1 to M1 ...\n");
        do_some_with_all_array_elem(N1, M1, cosh_minus_one);

        printf("\n\nStarted to fill M2 ...\n");
        generate_array(N2, M2, A, 10 * A, seed);

        printf("\n\nfunc M2[i+1]+M2[i] to M2 ...\n");
        preparing_M2(N2, M2, my_cbrt);

        printf("\n\nStarted to merge M1 and M2 ...\n");
        merge(N1, M1, N2, M2, min);
        printf("\n\nStarted to sort M2 ...\n");
        insertion_sort(N2, M2);
        for (int j = 0; j < N2; j++) {
            printf("\nM2[%d] = %f\n", j, M2[j]);
        }
        double result = reduce(N2,M2);
        printf("\n\n____________________________\nANSWER  = %f\n_______________________________\n\n",
               result);

    }
    gettimeofday(&T2, NULL);
    delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;
    printf("\nN=%d. Milliseconds passed: %ld\n", N1, delta_ms);
    return 0;
}

double reduce(int n, double array[]) {
    double sum_sin_even = 0;
    int min_not_zero_index = find_min_not_zero(n, array);
    printf("\nmin_not_zero_index = %d\n", min_not_zero_index);
    if (min_not_zero_index == -1) {
        printf("\nOnly zeros in array M2\n\n");
        return NAN;
    }
    for (int j = 0; j < n; j++) {
        double div_to_min = array[j] / array[min_not_zero_index];
        printf("\ndiv_to_min = %f\n", div_to_min);
        if ((int) floor(div_to_min) % 2 == 0) {
            printf("floor %f = %f", div_to_min, floor(div_to_min));
            sum_sin_even = sum_sin_even + sin(array[j]);
        }
    }
    printf("\nsum = %f\n", sum_sin_even);
    return sum_sin_even;
}

void merge(int array_len, double array[], int merge_array_len, double merge_array[], double (*merge_func)(double, double)) {
    int len = min(array_len, merge_array_len);
    for (int j = 0; j < len; j++) {
        printf("\narray[%d] = %f", j, array[j]);
        printf("\nmerge_array[%d] = %f\n", j, merge_array[j]);
        merge_array[j] = merge_func(array[j], merge_array[j]);
        printf("\nM2[%d] = %f\n", j, merge_array[j]);
    }
}

void preparing_M2(int n, double array[], double (*func)(double)) {
    for (int j = n - 1; j >= 0; j--) {
        if (j != 0) {
            array[j] = array[j - 1] + array[j];
        }
        array[j] = func(array[j]);
        printf("\narray[%d] = %f", j, array[j]);
    }
}

void do_some_with_all_array_elem(int n, double array[], double (*func)(double)) {
    for (int j = 0; j < n; j++) {
        array[j] = func(array[j]);
        printf("\narray[%d] = %f", j, array[j]);
    }
}

int find_min_not_zero(int n, double sorted_array[]) {
    for (int i = 0; i < n; i++) {
        if (sorted_array[i] != 0) {
            return i;
        }
    }
    return -1;
}

void generate_array(int n, double array[], int minValue, int maxValue, int seed) {
    for (int j = 0; j < n; j++) {
        array[j] = minValue + rand_r(&seed) % maxValue;
        printf("\narray[%d] = %f", j, array[j]);
    }
}

void insertion_sort(int n, double array[]) {
    int new_elem, location;
    for (int i = 1; i < n; i++) {
        new_elem = array[i];
        location = i - 1;
        while (location >= 0 && array[location] > new_elem) {
            array[location + 1] = array[location];
            location = location - 1;
        }
        array[location + 1] = new_elem;
    }
}

