//《基于MPI的大数据高性能计算导论》
// Frank Nielsen 张伟哲译 2018年7月第一版第一次印刷
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// filename: MPIHelloWorld.cpp
#include "mpi.h"
#include <iostream>
// mpiexec MPIHelloWorld.exe
int main(int argc, char* argv[])
{
    int id, size, name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    // Initialize MPI.
    //MPI::Init(argc, argv);
    //// Get the number of processes.
    //size = MPI_COMM_WORLD.Get_size();
    //// Get the individual process ID.
    //id = MPI::COMM_WORLD.Get_rank();
    //MPI_Get_processor_name(processor_name, &name_len);
    //// Print off a hello world message
    //std::cout << "  Processor " << processor_name << "  ID=" << id << " Welcome to MPI!'\n";
    //// Terminate MPI.
    //MPI::Finalize();
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Get_processor_name(processor_name, &name_len);
    std::cout << "Process " << processor_name << " ID= " << id << " Welcome to MPI!" << std::endl;
    MPI_Finalize();
    return 0;
}
// 运行结果
//```
//mpiexec MPIHelloWorld.exe
//Process lfy_p50 ID = 6 Welcome to MPI!
//Process lfy_p50 ID = 3 Welcome to MPI!
//Process lfy_p50 ID = 2 Welcome to MPI!
//Process lfy_p50 ID = 4 Welcome to MPI!
//Process lfy_p50 ID = 1 Welcome to MPI!
//Process lfy_p50 ID = 7 Welcome to MPI!
//Process lfy_p50 ID = 5 Welcome to MPI!
//Process lfy_p50 ID = 0 Welcome to MPI!
//```
