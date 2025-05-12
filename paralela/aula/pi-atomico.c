#include <stdio.h>
#include <omp.h>
#include <string.h>

static long num_steps = 100000;
double step;
#define NUM_THREADS 16

int main(void){

    int i, nthreads; double x, pi, sum = 0.0; //padding
    
    step = 1.0/(double) num_steps; //base

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(NUM_THREADS)
    {   
        while(i < num_steps){
            x = (i + 0.5) * step; //altura

            #pragma omp atomic
            sum += 4.0 / (1.0 + x*x);
            #pragma omp atomic
            ++i;
        }

    }
    pi = step * sum;

    double tempo = omp_get_wtime();
    tempo = tempo - start;
    printf("%lf %lf\n",pi, tempo);
    
    return 0;

}