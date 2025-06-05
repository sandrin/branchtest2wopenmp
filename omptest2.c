#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SIZE 32768
#define MOD 256
#define HMOD 128
#define ITERS 1000000

typedef struct
{
    int arr[SIZE];
    long long sum;
    double elapsed, sortedElapsed;
} stuff;

int compare(const void* arg1, const void* arg2)
{
    return (*(int*)arg1 - *(int*)arg2);
}

void sorted_branching(stuff* sb)
{
    unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)sb ^ omp_get_thread_num();
    for (int i = 0; i < SIZE; i++)
    {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        sb->arr[i] = seed % MOD;
    }

    double sortStart = omp_get_wtime();
    qsort(sb->arr, SIZE, sizeof(int), compare);
    sb->sortedElapsed = omp_get_wtime() - sortStart;

    double start = omp_get_wtime();
    long long total = 0;
    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < ITERS; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (sb->arr[j] >= HMOD) {total += sb->arr[j];}
        }
    }
    sb->sum = total;
    sb->elapsed = omp_get_wtime() - start;
}

void sorted_branching_2(stuff* sb2)
{
    unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)sb2 ^ omp_get_thread_num();
    for (int i = 0; i < SIZE; i++)
    {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        sb2->arr[i] = seed % MOD;
    }

    double sortStart = omp_get_wtime();
    qsort(sb2->arr, SIZE, sizeof(int), compare);
    sb2->sortedElapsed = omp_get_wtime() - sortStart;

    double start = omp_get_wtime();
    long long total = 0;
    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < ITERS; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            total = (sb2->arr[j] >= HMOD) ? total + sb2->arr[j] : total; //testing ternary operator branching
        }
    }
    sb2->sum = total;
    sb2->elapsed = omp_get_wtime() - start;    
}

void sorted_branchless(stuff* sbl)
{
    unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)sbl ^ omp_get_thread_num();
    for (int i = 0; i < SIZE; i++)
    {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        sbl->arr[i] = seed % MOD;
    }

    double sortStart = omp_get_wtime();
    qsort(sbl->arr, SIZE, sizeof(int), compare);
    sbl->sortedElapsed = omp_get_wtime() - sortStart;

    double start = omp_get_wtime();
    long long total = 0;
    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < ITERS; i++)
    {
        long long localSum = 0;
        for (int j = 0; j < SIZE; j++)
        {
            int t = (sbl->arr[j] - HMOD) >> 31;
            localSum += ~t & sbl->arr[j];
        }
        total += localSum;
    }
    sbl->sum = total;
    sbl->elapsed = omp_get_wtime() - start;
}

void unsorted_branching(stuff* usb)
{
    unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)usb ^ omp_get_thread_num();
    for (int i = 0; i < SIZE; i++)
    {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        usb->arr[i] = seed % MOD;
    }

    double start = omp_get_wtime();
    long long total = 0;
    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < ITERS; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (usb->arr[j] >= HMOD) {total += usb->arr[j];}
        }
    }
    usb->sum = total;
    usb->elapsed = omp_get_wtime() - start;
}

void unsorted_branching_2(stuff* usb2)
{
    unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)usb2 ^ omp_get_thread_num();
    for (int i = 0; i < SIZE; i++)
    {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        usb2->arr[i] = seed % MOD;
    }

    double start = omp_get_wtime();
    long long total = 0;
    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < ITERS; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            total = (usb2->arr[j] >= HMOD) ? total + usb2->arr[j] : total;
        }
    }
    usb2->sum = total;
    usb2->elapsed = omp_get_wtime() - start;
}

void unsorted_branchless(stuff* usbl)
{
    unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)usbl ^ omp_get_thread_num();
    for (int i = 0; i < SIZE; i++)
    {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        usbl->arr[i] = seed % MOD;
    }

    double start = omp_get_wtime();
    long long total = 0;
    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < ITERS; i++)
    {
        long long localSum = 0;
        for (int j = 0; j < SIZE; j++)
        {
            int t = (usbl->arr[j] - HMOD) >> 31;
            localSum += ~t & usbl->arr[j];
        }
        total += localSum;
    }
    usbl->sum = total;
    usbl->elapsed = omp_get_wtime() - start;
}

int main()
{
    stuff sb, sb2, sbl, usb, usb2, usbl;

    sorted_branching(&sb);
    sorted_branching_2(&sb2);
    sorted_branchless(&sbl);
    unsorted_branching(&usb);
    unsorted_branching_2(&usb2);
    unsorted_branchless(&usbl);

    printf("sorted branching    :time taken: %lf, sum: %lld, sorting time: %lf\n", sb.elapsed, sb.sum, sb.sortedElapsed);
    printf("sorted branching 2  :time taken: %lf, sum: %lld, sorting time: %lf\n", sb2.elapsed, sb2.sum, sb2.sortedElapsed);
    printf("sorted branchless   :time taken: %lf, sum: %lld, sorting time: %lf\n\n", sbl.elapsed, sbl.sum, sbl.sortedElapsed);

    printf("unsorted branching  :time taken: %lf, sum: %lld\n", usb.elapsed, usb.sum);
    printf("unsorted branching 2:time taken: %lf, sum: %lld\n", usb2.elapsed, usb2.sum);
    printf("unsorted branchless :time taken: %lf, sum: %lld\n\n", usbl.elapsed, usbl.sum);

    return 0;
}