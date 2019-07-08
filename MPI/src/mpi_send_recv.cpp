#include "mpi.h"
#include <iostream>

// https://mpitutorial.com/tutorials/mpi-send-and-receive/zh_cn/
// mpiexec -n 2 mpi_send_recv
int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    // Find out rank, size
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // We are assuming at least 2 processes for this task
    if (world_size < 2) {
        std::cerr << "World size must be greater than 1 for " << argv[0] << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int number;
    if (world_rank == 0) {
        // If we are rank 0, set the number to -1 and send it to process 1
        number = -1;
        MPI_Send(
            /* data         = */ &number,
            /* count        = */ 1,
            /* datatype     = */ MPI_INT,
            /* destination  = */ 1,
            /* tag          = */ 0,
            /* communicator = */ MPI_COMM_WORLD);
    }
    else if (world_rank == 1) {
        MPI_Recv(
            /* data         = */ &number,
            /* count        = */ 1,
            /* datatype     = */ MPI_INT,
            /* source       = */ 0,
            /* tag          = */ 0,
            /* communicator = */ MPI_COMM_WORLD,
            /* status       = */ MPI_STATUS_IGNORE);
        std::cout << "Process 1 received number " << number << " from process 0" << std::endl;
    }
    MPI_Finalize();
    return 0;
}
