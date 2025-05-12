#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
double step;

int main(void){

    int i; double pi, sum = 0.0;
    
    step = 1.0/(double) num_steps;

    double start = omp_get_wtime();
    #pragma omp parallel 
    {   
        double x;//privatização explic
        #pragma omp for schedule(dynamic) reduction (+:sum) //privatização explic
        //#pragma omp parallel for schedule(dynamic) reduction (+:sum)
        for(i = 0; i < num_steps; ++i){ // implicitamente privatiza i
            x = (i + 0.5) * step; //largura retangulo
            sum = sum + 4.0 / (1.0 + x*x);
            
        }
        pi = step * sum;
    }

    double tempo = omp_get_wtime();
    tempo = tempo - start;
    printf("%lf %lf\n",pi, tempo);

    return 0;

}

//slime chunck