
//
// Created by dinara on 11.03.23.
//
#include "lab1.h"
#include <omp.h>

#define N_THREADS 4
#define SCHEDULE_TYPE dynamic
#define SCHEDULE_CHUNK_SIZE 4

int main(int args, char *argv[])
{
    int i, N1, N2, A;
    struct timeval T1, T2;
    long delta_ms;
    N1 = atoi(argv[1]);
    N2 = N1 / 2;
    A = atoi(argv[2]);
    FILE *S1, *S2;
    const char *first = "_ans.txt";
    const char *second = "_delt.txt";
    char *filename = argv[3];
    char ans[512], delt[512];
    snprintf(ans, sizeof ans, "%s%s", filename, first);
    snprintf(delt, sizeof delt, "%s%s", filename, second);
    S1 = fopen(ans, "a");
    S2 = fopen(delt, "a");

    if (N1 == 0 || A == 0)
    {
        // printf("One or both args  = 0");
        return -1;
    }
    gettimeofday(&T1, NULL);

    // printf("Hello!");
    for (i = 0; i < 100; i++)
    {
        //        gettimeofday(&T1, NULL);
        //        srand(i);
        unsigned int seed = i;
        double *M1 = malloc(sizeof(double) * N1);
        double *M2 = malloc(sizeof(double) * N2);
        generate_array(N1, M1, 1, A, seed);

        do_some_with_all_array_elem(N1, M1, cosh_minus_one);

        generate_array(N2, M2, A, 10 * A, seed);

        preparing_M2(N2, M2, my_cbrt);

        merge(N1, M1, N2, M2, min);

        my_q_sort(N2, M2);

        double result = reduce(N2, M2);
        free(M1);
        free(M2);
        fprintf(S1, "%d %f\n", i, result);
    }

    gettimeofday(&T2, NULL);
    delta_ms = 1000000 * (T2.tv_sec - T1.tv_sec) + T2.tv_usec - T1.tv_usec;
    //    delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;
    printf("\nN=%d. Milliseconds passed: %ld\n", N1, delta_ms);
    fprintf(S2, "%d %ld\n", N1, delta_ms);
    fclose(S1);
    fclose(S2);
    return 0;
}

double reduce(int n, double array[])
{
    double sum_sin_even = 0;
    int min_not_zero_index = find_min_not_zero(n, array);
    // printf("\nmin_not_zero_index = %d\n", min_not_zero_index);
    if (min_not_zero_index == -1)
    {
        // printf("\nOnly zeros in array M2\n\n");
        return NAN;
    }
    int j;
#pragma omp parallel for default(none) private(j) shared(n, min_not_zero_index, array) reduction(+ \
                                                                                                 : sum_sin_even) num_threads(N_THREADS) schedule(SCHEDULE_TYPE, SCHEDULE_CHUNK_SIZE)
    for (j = 0; j < n; j++)
    {
        double div_to_min = array[j] / array[min_not_zero_index];
        // printf("\ndiv_to_min = %f\n", div_to_min);
        if ((int)floor(div_to_min) % 2 == 0)
        {
            // printf("floor %f = %f", div_to_min, floor(div_to_min));
            sum_sin_even = sum_sin_even + sin(array[j]);
        }
    }

    return sum_sin_even;
}

void merge(int array_len, double array[], int merge_array_len, double merge_array[], double (*merge_func)(double, double))
{
    int len = min(array_len, merge_array_len);
    int j;
#pragma omp parallel for default(none) private(j) shared(array, merge_array, len, merge_func) num_threads(N_THREADS) schedule(SCHEDULE_TYPE, SCHEDULE_CHUNK_SIZE)
    for (j = 0; j < len; j++)
    {
        // printf("\narray[%d] = %f", j, array[j]);
        // printf("\nmerge_array[%d] = %f\n", j, merge_array[j]);
        //        printf("Num threads = %d", omp_get_num_threads());
        merge_array[j] = merge_func(array[j], merge_array[j]);
        // printf("\nM2[%d] = %f\n", j, merge_array[j]);
    }
}

void preparing_M2(int n, double array[], double (*func)(double))
{
    double *tmp_array = malloc(sizeof(double) * n);
    copy_array(array, tmp_array, n);
    int j;
#pragma omp parallel for default(none) private(j) shared(array, tmp_array, n, func) num_threads(N_THREADS) schedule(SCHEDULE_TYPE, SCHEDULE_CHUNK_SIZE)
    for (j = n - 1; j >= 0; j--)
    {
        if (j != 0)
        {
            array[j] = tmp_array[j - 1] + tmp_array[j];
        }
        array[j] = func(array[j]);
        //
//        printf("\narray[%d] = %f", j, array[j]);
    }
    free(tmp_array);
}

void copy_array(double from_array[], double to_array[], int len)
{
    int i;
#pragma omp parallel for default(none) private(i) shared(from_array, to_array, len) num_threads(N_THREADS) schedule(SCHEDULE_TYPE, SCHEDULE_CHUNK_SIZE)
    for (i = 0; i < len; i++)
    {
        to_array[i] = from_array[i];
        //        printf("Num threads = %d", omp_get_num_threads());
    }
}

void do_some_with_all_array_elem(int n, double array[], double (*func)(double))
{
    int j;
#pragma omp parallel for default(none) private(j) shared(n, array, func) num_threads(N_THREADS) schedule(SCHEDULE_TYPE, SCHEDULE_CHUNK_SIZE)
    for (j = 0; j < n; j++)
    {
        array[j] = func(array[j]);
        // printf("\narray[%d] = %f", j, array[j]);
        //        printf("Num threads = %d", omp_get_num_threads());
    }
}

int find_min_not_zero(int n, double sorted_array[])
{
    int i;
    double min_index = 0;
#pragma omp parallel for default(none) private(i) shared(n, sorted_array, min_index) num_threads(N_THREADS) schedule(SCHEDULE_TYPE, SCHEDULE_CHUNK_SIZE)
    for (i = 1; i < n; i++)
    {
        if (sorted_array[i]>0 && sorted_array[i-1]==0)
        {
            min_index = i;
        }
    }
    if(sorted_array[n-1]==0) min_index = -1;
    return min_index;
}

void generate_array(int n, double array[], int minValue, int maxValue, unsigned int seed)
{
    int j;
    // Problem with parallelizing wrong anxwers
//#pragma omp parallel for default(none) private(j) shared(n,array,minValue,maxValue,seed) num_threads(N_THREADS) schedule(SCHEDULE_TYPE, SCHEDULE_CHUNK_SIZE)
    for (j = 0; j < n; j++)
    {
        int r;
        // rand_r не распараллелить посмотреть реализацию самой функции
        r = rand_r(&seed);
        array[j] = minValue + r % maxValue;
    }
}

void insertion_sort(int n, double array[])
{
    double new_elem;
    int location;
    for (int i = 1; i < n; i++)
    {
        new_elem = array[i];
        location = i - 1;
        while (location >= 0 && array[location] > new_elem)
        {
            array[location + 1] = array[location];
            location = location - 1;
        }
        array[location + 1] = new_elem;
    }
}

void quick_sort_parallel(int left, int right, double array[])
{
    int i = left, j = right;
    double pivot = array[(left + right) / 2];
    double temp;

    while (i <= j)
    {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i <= j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }

#pragma omp task
    if (left < j)
        quick_sort_parallel(left, j, array);

#pragma omp task
    if (i < right)
        quick_sort_parallel(i, right, array);
}

void my_q_sort(int n, double array[])
{
#pragma omp parallel // вообще надо здесь?
#pragma omp single
    quick_sort_parallel(0, n - 1, array);
}

double cosh_minus_one(double x)
{
    return cosh(x) - 1;
}

double my_cbrt(double x)
{
    return cbrt(M_PI * x);
}

double min(double a, double b)
{
    return a >= b ? b : a;
}