//
// Created by dinara on 11.03.23.
//
#ifndef PARALLEL_PROGRAMMING_LAB1_H
#define PARALLEL_PROGRAMMING_LAB1_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

int find_min_not_zero(int n, double sorted_array[]);
void generate_array(int n, double array[], int minValue, int maxValue, unsigned int seed);
void do_some_with_all_array_elem(int n, double array[], double (*func)(double));
void preparing_M2(int n, double array[], double (*func)(double));
void merge(int array_len, double array[], int merge_array_len, double merge_array[], double (*merge_func)(double, double));
double reduce(int n, double array[]);
void insertion_sort(int n, double mass[]);
void copy_array(double from_array[], double to_array[], int len);
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
#endif // PARALLEL_PROGRAMMING_LAB1_H