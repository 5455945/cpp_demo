//《基于MPI的大数据高性能计算导论》
// Frank Nielsen 张伟哲译 2018年7月第一版第一次印刷
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// filename: MPIOpenMPExample.cpp
#include "mpi.h"
#include "omp.h"
#include <cstdio>
// mpiexec MPIOpenMPExample.exe
int main(int argc, char* argv[])
{
    int rank, nprocs, thread_id, nthreads;
    int name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &name_len);

#pragma omp parallel private(thread_id, nthreads)
    {
        thread_id = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        printf("Thread number %d (on %d) for the MPI process number %d (on %d) [%s]\n",
            thread_id, nthreads, rank, nprocs, processor_name);
    }
    MPI_Finalize();
    return 0;
}
// 运行结果
//```
//mpiexec MPIOpenMPExample.exe
//Thread number 0 (on 1) for the MPI process number 3 (on 8)[lfy_p50]
//Thread number 0 (on 1) for the MPI process number 7 (on 8)[lfy_p50]
//Thread number 0 (on 1) for the MPI process number 6 (on 8)[lfy_p50]
//Thread number 0 (on 1) for the MPI process number 5 (on 8)[lfy_p50]
//Thread number 0 (on 1) for the MPI process number 1 (on 8)[lfy_p50]
//Thread number 0 (on 1) for the MPI process number 0 (on 8)[lfy_p50]
//Thread number 0 (on 1) for the MPI process number 4 (on 8)[lfy_p50]
//Thread number 0 (on 1) for the MPI process number 2 (on 8)[lfy_p50]
//```
