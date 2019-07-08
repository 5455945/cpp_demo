//《基于MPI的大数据高性能计算导论》
// Frank Nielsen 张伟哲译 2018年7月第一版第一次印刷
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// filename: MPINonBlockingCommunication.cpp
#include "mpi.h"
#include <cstdio>
// mpiexec MPINonBlockingCommunication.exe
int main(int argc, char** argv)
{
    int myid, numprocs;
    int tag, source, destination, count;
    int buffer;
    MPI_Status status;
    MPI_Request request;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    tag = 1; // any integer to tag messages
    source = 0;
    destination = 1;
    count = 1;
    buffer = 0;
    request = MPI_REQUEST_NULL;
    if (myid == source) {
        buffer = 2015;
        MPI_Isend(&buffer, count, MPI_INT, destination, tag, MPI_COMM_WORLD, &request);
    }
    if (myid == destination) {
        MPI_Irecv(&buffer, count, MPI_INT, source, tag, MPI_COMM_WORLD, &request);
    }
    MPI_Wait(&request, &status);
    if (myid == source) {
        printf("processor %d sent %d\n", myid, buffer);
    }
    if (myid == destination) {
        printf("processor %d received %d\n", myid, buffer);
    }
    MPI_Finalize();
    return 0;
}
// 运行结果
//```
//mpiexec MPINonBlockingCommunication.exe
//processor 1 received 2015
//processor 0 sent 2015
//```

//int main(int argc, char** argv)
//{
//    int numtasks, rank, next, prev, buf[2],tag1, tag2;
//    tag1 = tag2 = 0;
//    MPI_Request reqs[4];
//    MPI_Status stats[4];
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    prev = rank - 1;
//    next = rank + 1;
//    if (rank == 0)
//        prev = numtasks - 1;
//    if (rank == numtasks - 1)
//        next = 0;
//
//    MPI_Irecv(&buf[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[0]);
//    MPI_Irecv(&buf[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[1]);
//    MPI_Isend(&rank, 1, MPI_INT, prev, tag2, MPI_COMM_WORLD, &reqs[2]);
//    MPI_Isend(&rank, 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &reqs[3]);
//    MPI_Waitall(4, reqs, stats);
//    printf("Task %d communicated with tasks %d & %d\n", rank, prev, next);
//
//    MPI_Finalize();
//    return 0;
//}
// 运行结果
//```
//mpiexec MPINonBlockingCommunication.exe
//Task 1 communicated with tasks 0 & 2
//Task 0 communicated with tasks 7 & 1
//Task 5 communicated with tasks 4 & 6
//Task 7 communicated with tasks 6 & 0
//Task 3 communicated with tasks 2 & 4
//Task 6 communicated with tasks 5 & 7
//Task 4 communicated with tasks 3 & 5
//Task 2 communicated with tasks 1 & 3
//```
