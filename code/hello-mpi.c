#include <stdio.h>
#include <mpi.h>

int main(int argc, char * argv[])
{
    MPI_Init(&argc, &argv);

    int wrank, wsize;
    MPI_Comm_rank(MPI_COMM_WORLD, &wrank);
    MPI_Comm_size(MPI_COMM_WORLD, &wsize);

    int nrank, nsize;
    MPI_Comm MPI_COMM_NODE;
    MPI_Comm_split_type(MPI_COMM_WORLD, MPI_COMM_TYPE_SHARED, 0 /* key */, MPI_INFO_NULL, &MPI_COMM_NODE);
    MPI_Comm_rank(MPI_COMM_NODE, &nrank);
    MPI_Comm_size(MPI_COMM_NODE, &nsize);

    int *   shptr = NULL;
    MPI_Win shwin;
    MPI_Info win_info;
    MPI_Info_create(&win_info);
    MPI_Info_set(win_info, "alloc_shared_noncontig", "true");
    MPI_Win_allocate_shared(sizeof(int), sizeof(int), win_info, MPI_COMM_WORLD, &shptr, &shwin);
    MPI_Info_free(&win_info);

    MPI_Win_lock_all(0 /* assertion */, shwin);

    MPI_Win_sync(shwin);
    MPI_Barrier(MPI_COMM_NODE);
    MPI_Win_sync(shwin);

    MPI_Aint rsize[nsize];
    int rdisp[nsize];
    int * rptr[nsize];
    for (int i=0; i<nsize; i++) {
        MPI_Win_shared_query(shwin, i, &(rsize[i]), &(rdisp[i]), &(rptr[i]));
        printf("rank=%d target=%d rptr=%p rsize=%zu rdisp=%d \n", nrank, i, rptr[i], (size_t)rsize[i], rdisp[i]);
    }

    MPI_Win_unlock_all(shwin);

    MPI_Win_free(&shwin);

    MPI_Comm_free(&MPI_COMM_NODE);
    MPI_Finalize();

    return 0;
}
