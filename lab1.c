//
// Created by dinara on 11.03.23.
//

#include "lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

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
    }
    gettimeofday(&T2,NULL);
    delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec)/1000;
    printf("\nN=%d. Milliseconds passed: %ld\n",N,delta_ms);
    return 0;
}