//������MPI�Ĵ����ݸ����ܼ��㵼�ۡ�
// Frank Nielsen ��ΰ���� 2018��7�µ�һ���һ��ӡˢ
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
// ���н��
//```
//mpiexec MPISynchronizeTime.exe
//0.000101379
//```
