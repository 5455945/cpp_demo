//《基于MPI的大数据高性能计算导论》
// Frank Nielsen 张伟哲译 2018年7月第一版第一次印刷
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// filename: MPIFactorialReduce.cpp
#include "mpi.h"
#include <iostream>
// mpiexec MPIFactorialReduce.exe
int main(int argc, char* argv[])
{
    int i, me, nprocs;
    int number, globalFact = -1, localFact;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);

    number = me + 1;
    MPI_Reduce(&number, &globalFact, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
    if (me == 0) {
        printf("Computing the factorial in MPI: %d processus = %d\n", nprocs, globalFact);
    }

    localFact = 1;
    for (i = 0; i < nprocs; i++) {
        localFact *= (i + 1);
    }

    if (me == 0) {
        printf("Versus local factorial: %d\n", localFact);
    }

    MPI_Finalize();
    return 0;
}
// 运行结果
//```
//mpiexec MPIFactorialReduce.exe
//Computing the factorial in MPI : 8 processus = 40320
//Versus local factorial : 40320
//```
