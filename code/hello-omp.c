#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char * argv[])
{
    _Pragma("omp parallel")
    {
        int nrank = omp_get_thread_num();
        int nsize = omp_get_num_threads();

        int * ptrs[nsize];
        ptrs[nrank] = malloc(sizeof(int));

        _Pragma("omp flush")
        _Pragma("omp barrier")
        _Pragma("omp flush")

        for (int i=0; i<nsize; i++) {
            printf("rank=%d target=%d rptr=%p \n", nrank, i, ptrs[i]);
        }

        free(ptrs[nrank]);
    }
    return 0;
}
