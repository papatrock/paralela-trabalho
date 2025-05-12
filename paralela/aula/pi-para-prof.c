#include <stdio.h>
#include <omp.h>
#include <string.h>

static long num_steps = 100000;
double step;
#define NUM_THREADS 16

int main(void){

    int i, nthreads; double pi, sum[NUM_THREADS][8]; //padding
    
    step = 1.0/(double) num_steps; //base

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int i, id, nthreds; double x;
        id = omp_get_thread_num();
        nthreds = omp_get_num_threads();
        if(id == 0) nthreads = nthreds;
        for(i = id, sum[id][0] = 0.0; i < num_steps; i = i+nthreds){
            x = (i + 0.5) * step; //altura
            sum[id][0] += 4.0 / (1.0 + x*x);
        }
    }

    for(i = 0, pi = 0.0; i < nthreads; ++i){
        pi += sum[i][0] * step;

    }

    double tempo = omp_get_wtime();
    tempo = tempo - start;
    printf("%lf %lf\n",pi, tempo);
    
    return 0;

}