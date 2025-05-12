#include <stdio.h>
#include <omp.h>
#include <string.h>

static long num_steps = 100000;
double step;
#define NUM_THREADS 16

int main(void){

    int i; double x, pi, sum = 0.0;
    
    int sumparc [NUM_THREADS];
    memset(sumparc, 0, sizeof(sumparc));
    

    int stepT = num_steps / NUM_THREADS;
    step = 1.0/(double) num_steps; //base

    #pragma omp parallel num_threads(16)
    {
        int ID = omp_get_thread_num();
        printf("thread %d, indo de %d até %d\n",ID, i, stepT * (ID + 1));
        for(i = (ID)*stepT; i < stepT * (ID + 1); ++i){
            x = (i + 0.5) * step; //altura
            sumparc[ID] = sumparc[ID] + 4.0 / (1.0 + x*x);
        }
    }

    for(int j = 0; j < NUM_THREADS; ++j)
        sum = sumparc[j] + sum;

    printf("sum: %d\n",sum);

    pi = step * sum;

    printf("pi %lf\n",pi);
    return 0;

}