//《基于MPI的大数据高性能计算导论》
// Frank Nielsen 张伟哲译 2018年7月第一版第一次印刷
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
    std::random_device rd;  // 将用于获得随机数引擎的种子
    std::mt19937 gen(rd()); // 以 rd() 播种的标准 mersenne_twister_engine
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
// 运行结果
//```
//mpiexec MPIMinimumReduce.exe
//minimal value 0.000059 on proc. 0  at location 303
//```
