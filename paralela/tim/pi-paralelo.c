/*
  Exercicio 1 do mano tim, paralelizar o algoritimo do calculo do pi
*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define NUM_THREADS 64

static long num_steps = 100000;
double step;

int main(void)
{

  double pi, sum = 0.0, parcial_sum[NUM_THREADS];
  int i, nthreads;

  step = 1.0 / (double)num_steps;

  double inicio = omp_get_wtime();
#pragma omp parallel num_threads(NUM_THREADS)
  {
    int ID = omp_get_thread_num(), num_threads = omp_get_num_threads();
    int i; // variavel local
    double x;
    if (ID == 0)
      nthreads = num_threads;
    for (i = ID, parcial_sum[ID] = 0.0; i < num_steps; i += nthreads)
    {                       // cada thread começa no index ID e soma + NUMERO DE THREADS por iteração
      x = (i + 0.5) * step; // largura retangulo
      parcial_sum[ID] += 4.0 / (1.0 + x * x);
    }
  }

  for (i = 0, pi = 0.0; i < nthreads; ++i)
  {
    pi += parcial_sum[i] * step;
  }
  double fim = omp_get_wtime();
  printf("pi %lf, tempo: %lf\n", pi, fim - inicio);
  return 0;
}