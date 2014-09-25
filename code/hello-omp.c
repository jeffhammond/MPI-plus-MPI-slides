#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int main(int argc, char * argv[])
{
    int ** shrptrs;

    _Pragma("omp parallel")
    {
        int nrank = omp_get_thread_num();
        int nsize = omp_get_num_threads();

        printf("thread %d of %d\n", nrank, nsize);

        _Pragma("omp master")
        {
            shrptrs = malloc(nsize*sizeof(int*));
        }
        _Pragma("omp barrier") /* master does not imply barrier */

        shrptrs[nrank] = calloc(1,sizeof(int));

        _Pragma("omp flush")
        _Pragma("omp barrier")

        for (int i=0; i<nsize; i++) {
            printf("rank=%d target=%d rptr=%p \n", nrank, i, shrptrs[i]);
        }

        free(shrptrs[nrank]);

        _Pragma("omp barrier") /* master does not imply barrier */
        _Pragma("omp master")
        {
            free(shrptrs);
        }
    }
    return 0;
}
