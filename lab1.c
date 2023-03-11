//
// Created by dinara on 11.03.23.
//

#include "lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>


int find_min_not_zero(int n, double sorted_array[]);

void insertion_sort(int n, double mass[])
{
    int newElement, location;
    for (int i = 1; i < n; i++){
        newElement = mass[i];
        location = i - 1;
        while(location >= 0 && mass[location] > newElement)
        {
            mass[location+1] = mass[location];
            location = location - 1;
            }
        mass[location+1] = newElement;
        }
}

int main(int args, char* argv[]){
    int i, N, A;
    struct timeval T1, T2;
    long delta_ms;
    N = atoi(argv[1]);
    A = atoi(argv[2]);
    gettimeofday(&T1, NULL);
    double M1[N], M2[N/2];
    printf("Hello!");
    for(i = 0; i<100;i++){
        srand(i);
        printf("i = %d",i);
        int seed = i;
        printf("\n\nStarted to fill M1 ...\n");
        for (int j = 0; j< N;j++){
            M1[j] = 1+rand_r(&seed)%A;
            printf("\nM1[%d] = %f",j, M1[j]);
        }
        printf("\n\nfunc cosh(num) - 1 to M1 ...\n");
        for (int j = 0; j< N;j++){
            M1[j] = cosh(M1[j])-1;
            printf("\nM1[%d] = %f",j, M1[j]);
        }
        printf("\n\nStarted to fill M2 ...\n");
        for (int j = 0; j< N/2;j++){
            M2[j] = A+rand_r(&seed)%(10*A);
            printf("\nM2[%d] = %f",j, M2[j]);
        }
        printf("\n\nfunc M2[i+1]+M2[i] to M2 ...\n");
        for (int j = N/2-1; j>0;j--){
            M2[j]= M2[j-1] + M2[j];
            M2[j]=  cbrt(M_PI*M2[j]);
            printf("\nM2[%d] = %f",j, M2[j]);
        }
        printf("\n\nStarted to merge M1 and M2 ...\n");
        for (int j = 0; j< N/2;j++){
            printf("\nM1[%d] = %f",j, M1[j]);
            printf("\nM2[%d] = %f\n",j, M2[j]);
            M2[j] = M2[j]>=M1[j]? M1[j]:M2[j];
            printf("\nM2[%d] = %f\n",j, M2[j]);
        }
        printf("\n\nStarted to sort M2 ...\n");
        insertion_sort(N/2,M2);
        for (int j = 0; j< N/2;j++){
            printf("\nM2[%d] = %f\n",j, M2[j]);
        }
        double sum_sin_even = 0;
        int min_not_zero_index = find_min_not_zero(N/2,M2);
        printf("\nmin_not_zero_index = %d\n", min_not_zero_index);
        if (min_not_zero_index==-1){
            printf("\nOnly zeros in array M2\n\n");
            return -1;
        }
        for (int j = 0; j< N/2;j++){
            double div_to_min = M2[j]/M2[min_not_zero_index];
            printf("\ndiv_to_min = %f\n",div_to_min);
            if ((int)floor(div_to_min)%2==0){
                printf("floor %f = %f",div_to_min,floor(div_to_min));
                sum_sin_even = sum_sin_even + sin(M2[j]);
            }
        }
        printf("\n\n____________________________\nANSWER sum_sin_even = %f\n_______________________________\n\n", sum_sin_even);

    }
    gettimeofday(&T2,NULL);
    delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec)/1000;
    printf("\nN=%d. Milliseconds passed: %ld\n",N,delta_ms);
    return 0;
}

int find_min_not_zero(int n, double sorted_array[]) {
    for (int i = 0; i < n; i++){
        if (sorted_array[i]!=0){
            return i;
        }
    }
    return -1;
}
