//《基于MPI的大数据高性能计算导论》
// Frank Nielsen 张伟哲译 2018年7月第一版第一次印刷
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// filename: MPICommunicatorRemoveFirstProcess.cpp
#include "mpi.h"
#include <cstdio>
// mpiexec MPICommunicatorRemoveFirstProcess.exe
int main(int argc, char** argv)
{
    MPI_Comm comm_world, comm_worker;
    MPI_Group group_world, group_worker;
    comm_world = MPI_COMM_WORLD;

    MPI_Init(&argc, &argv);

    MPI_Comm_group(comm_world, &group_world);
    MPI_Group_excl(group_world, 1, 0, &group_worker);

    // process 0 is removed from the communication

    MPI_Comm_create(comm_world, group_worker, &comm_worker);

    MPI_Finalize();
    return 0;
}
