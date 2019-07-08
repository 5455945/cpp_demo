#include "mpi.h"
#include <iostream>

// mpiexec -n 8 mpi_hello
int main() {
    // 初始化 MPI 环境
    MPI_Init(NULL, NULL);

    // 通过调用以下方法来得到所有可以工作的进程数量
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // 得到当前进程的秩
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // 得到当前进程的名字
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // 打印一条带有当前进程名字，秩以及
    // 整个 communicator 的大小的 hello world 消息。
    std::cout << "Hello world from processor " << processor_name << ", rank " 
        << world_rank << " out of " << world_size << " processors" << std::endl;

    // 释放 MPI 的一些资源
    MPI_Finalize();
    return 0;
}