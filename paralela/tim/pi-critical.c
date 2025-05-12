/*
  Exercicio 3 do mano tim:
    Utilizar as diretivas de sincronização para refazer o exercicio 1, sem falso compartilhamento
*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define NUM_THREADS 64

static long num_steps = 100000;
double step;

int main(void)
{

  double pi, sum = 0.0;
  int i, nthreads;

  step = 1.0 / (double)num_steps;

  double inicio = omp_get_wtime();
#pragma omp parallel num_threads(NUM_THREADS)
  {
    int ID = omp_get_thread_num(), num_threads = omp_get_num_threads();
    int i; // variavel local
    double x, local_sum = 0.0;
    if (ID == 0)
      nthreads = num_threads;
    for (i = ID; i < num_steps; i += num_threads)
    {                       // cada thread começa no index ID e soma + NUMERO DE THREADS por iteração
      x = (i + 0.5) * step; // largura retangulo
      local_sum += 4.0 / (1.0 + x * x);
    }
#pragma omp critical
    sum += local_sum; // variavel global, area critica
  }

  pi = sum * step;

  double fim = omp_get_wtime();
  printf("pi %lf, tempo: %lf\n", pi, fim - inicio);
  return 0;
}