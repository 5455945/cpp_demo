//������MPI�Ĵ����ݸ����ܼ��㵼�ۡ�
// Frank Nielsen ��ΰ���� 2018��7�µ�һ���һ��ӡˢ
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// filename: MPIMinimumReduce.cpp
#include "mpi.h"
#include <iostream>
#include <cstdlib>
#include <random>
// mpiexec MPIMinimumReduce.exe
int main(int argc, char* argv[])
{
    const int N = 1000;
    int rank, nprocs, i;
    const int root = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    float val[N];
    int minrank, minindex;
    float minval;

    // fill the array with random values (assume UNIX here)
    //srand(2312 + rank);
    //for (i = 0; i < N; i++) { 
    //    val[i] = drand48();
    //}
    std::random_device rd;  // �����ڻ����������������
    std::mt19937 gen(rd()); // �� rd() ���ֵı�׼ mersenne_twister_engine
    std::uniform_real_distribution<> dis(0, 1);
    for (i = 0; i < N; i++) { 
        val[i] = (float)dis(gen);
    }

    // Declare a C structure
    struct { float value;  int   index; } in, out;

    // First, find the minimum value locally
    in.value = val[0]; in.index = 0;
    for (i = 1; i < N; i++) {
        if (in.value > val[i]) {
            in.value = val[i];  in.index = i;
        }
    }

    // and get the global rand index
    in.index = rank * N + in.index;

    // now the compute the global minimum
    MPI_Reduce((void*)& in, (void*)& out, 1, MPI_FLOAT_INT, MPI_MINLOC, root, MPI_COMM_WORLD);

    if (rank == root) {
        minval = out.value; minrank = out.index / N;  minindex = out.index % N;
        printf("minimal value %f on proc. %d  at location %d\n", minval, minrank, minindex);
    }

    MPI_Finalize();
    return 0;
}
// ���н��
//```
//mpiexec MPIMinimumReduce.exe
//minimal value 0.000059 on proc. 0  at location 303
//```
