#include <mpi.h>
#include <stdio.h>

int main(int argc,char*argv[])
{
    int size;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    printf("%d \n",size);
    MPI_Finalize();
    return 0;
}
