#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
double step;

int main(void)
{

    int i;
    double x, pi, sum = 0.0;

    step = 1.0 / (double)num_steps;
    double inicio = omp_get_wtime();
    for (i = 0; i < num_steps; ++i)
    {
        x = (i + 0.5) * step; // largura retangulo
        sum = sum + 4.0 / (1.0 + x * x);
    }
    pi = step * sum;

    double fim = omp_get_wtime();
    printf("pi %lf, tempo: %lf\n", pi, fim - inicio);
    return 0;
}