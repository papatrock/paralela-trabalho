#include <stdio.h>
#include <omp.h>

//objdump -d
// zmm ymm -- registradores vetoriais
#define N 10

double work(double *a, double *b, int n){

    int i;

    double tmp, sum;

    sum = 0.0;

    //#pragma omp simd private(tmp) reduction(+:sum)
    for(i = 0; i < n; i++){
        tmp = a[i] + b[i];
        sum += tmp;
    }

    return sum;
}

//gcc simd-exemplo.c -fopenmp -o simd-exemplo
int main(void){
    double a[N] = {10,9,8,7,6,5,4,3,2,1};
    double b[N] = {1,2,3,4,5,6,7,8,9,10};

    printf("%ld\n",work(a,b,N));

    return 0;
}
