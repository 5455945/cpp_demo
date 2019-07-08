//《基于MPI的大数据高性能计算导论》
// Frank Nielsen 张伟哲译 2018年7月第一版第一次印刷
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// filename: MPICommunicatorSplitProcess.cpp
#include "mpi.h"
#include <cstdio>
// mpiexec MPICommunicatorSplitProcess.exe
#define NPROCS 8
int main(int argc, char* argv[])
{
    int ranks1[4] = { 0,1,2,3 }, ranks2[4] = { 4,5,6,7 };
    int rank;
    int new_rank = -1;
    int sendbuf = -1;
    int recvbuf = -1;
    MPI_Group orig_group, new_group;
    MPI_Comm new_comm;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    sendbuf = rank;

    // Retrieve the intial group  
    MPI_Comm_group(MPI_COMM_WORLD, &orig_group);

    if (rank < NPROCS / 2)
        MPI_Group_incl(orig_group, NPROCS / 2, ranks1, &new_group);
    else
        MPI_Group_incl(orig_group, NPROCS / 2, ranks2, &new_group);

    // create new communicator   
    MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);

    // global computation primitive 
    MPI_Allreduce(&sendbuf, &recvbuf, 1, MPI_INT, MPI_SUM, new_comm);
    MPI_Group_rank(new_group, &new_rank);
    printf("rank= %d newrank= %d recvbuf= %d\n", rank, new_rank, recvbuf);

    MPI_Finalize();
    return 0;
}
// 运行结果
//```
//mpiexec MPICommunicatorSplitProcess.exe
//rank = 2 newrank = 2 recvbuf = 6
//rank = 7 newrank = 3 recvbuf = 22
//rank = 5 newrank = 1 recvbuf = 22
//rank = 1 newrank = 1 recvbuf = 6
//rank = 6 newrank = 2 recvbuf = 22
//rank = 0 newrank = 0 recvbuf = 6
//rank = 3 newrank = 3 recvbuf = 6
//rank = 4 newrank = 0 recvbuf = 22
//```
