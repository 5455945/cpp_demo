//《基于MPI的大数据高性能计算导论》
// Frank Nielsen 张伟哲译 2018年7月第一版第一次印刷
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// filename: MPIRingBroadcast.cpp
#include "mpi.h"
#include <iostream>
// mpiexec MPIRingBroadcast.exe
int main(int argc, char* argv[])
{
    int rank, value, size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    do {
        if (rank == 0) {
            std::cin >> value;
            // Master node sends out the value
            MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }
        else {
            // Slave nodes block on receive the send on the value
            MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
            if (rank < size - 1) {
                MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            }
            std::cout << "process " << rank << " got " << value << std::endl;
        }
    } while (value >= 0);
    MPI_Finalize();

    return 0;
}
// 运行结果
//```
//mpiexec MPIRingBroadcast.exe
//1
//process 1 got 1
//process 2 got 1
//process 3 got 1
//process 4 got 1
//process 5 got 1
//process 6 got 1
//process 7 got 1
//- 5
//process 1 got - 5
//process 2 got - 5
//process 3 got - 5
//process 4 got - 5
//process 5 got - 5
//process 6 got - 5
//process 7 got - 5
//```
