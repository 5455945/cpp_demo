//《基于MPI的大数据高性能计算导论》
// Frank Nielsen 张伟哲译 2018年7月第一版第一次印刷
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// 阻塞通信demo
// filename: MPIBlockingCommunication.cpp
#include "mpi.h"
#include <cstdio>
// mpiexec MPIBlockingCommunication.exe
int main(int argc, char** argv)
{
    int myid, numprocs;
    int tag, source, destination, count;
    int buffer;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    tag = 2312; // any integer to tag messages
    source = 0;
    destination = 1;
    count = 1;
    if (myid == source) {
        buffer = 2015;
        MPI_Send(&buffer, count, MPI_INT, destination, tag, MPI_COMM_WORLD);
        printf("processor %d  sent %d\n", myid, buffer);
    }
    if (myid == destination) {
        MPI_Recv(&buffer, count, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        printf("processor %d received %d \n", myid, buffer);
    }
    MPI_Finalize();
}

// 运行结果
//```
//mpiexec MPIBlockingCommunication.exe
//processor 0  sent 2015
//processor 1 received 2015
//```
