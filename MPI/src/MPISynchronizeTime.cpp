//《基于MPI的大数据高性能计算导论》
// Frank Nielsen 张伟哲译 2018年7月第一版第一次印刷
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// filename: MPISynchronizeTime.cpp
#include "mpi.h"
#include <iostream>
// mpiexec MPISynchronizeTime.exe
int main(int argc, char** argv)
{
    double start, end;
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Barrier(MPI_COMM_WORLD); // important
    start = MPI_Wtime();

    // some local computations here
    MPI_Barrier(MPI_COMM_WORLD); // important
    end = MPI_Wtime(); // measure the worst-case time of

    MPI_Finalize();
    if (rank == 0) {
        std::cout << end - start << std::endl;
    }
    return 0;
}
// 运行结果
//```
//mpiexec MPISynchronizeTime.exe
//0.000101379
//```
