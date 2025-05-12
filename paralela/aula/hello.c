#include <stdio.h>
#include <omp.h>

int main(void){

    int ID = omp_get_thread_num();

    #pragma omp parallel num_threads(4)
    {
        printf("Hello (%d)",ID);
        printf("World (%d)\n",ID);

    }

    return 0;
}