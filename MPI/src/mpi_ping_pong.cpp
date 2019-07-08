#include "mpi.h"
#include <iostream>

// https://mpitutorial.com/tutorials/mpi-send-and-receive/zh_cn/
// mpiexec -n 2 mpi_ping_pong
int main(int argc, char** argv) {
    const int PING_PONG_LIMIT = 10;

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    // Find out rank, size
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // We are assuming at least 2 processes for this task
    if (world_size != 2) {
        std::cerr << "World size must be two for " << argv[0] << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int ping_pong_count = 0;
    int partner_rank = (world_rank + 1) % 2;
    while (ping_pong_count < PING_PONG_LIMIT) {
        if (world_rank == ping_pong_count % 2) {
            // Increment the ping pong count before you send it
            ping_pong_count++;
            MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            std::cout << world_rank << " sent and incremented ping_pong_count " 
                << ping_pong_count << " to " << partner_rank << std::endl;
        }
        else {
            MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD,
                MPI_STATUS_IGNORE);
            std::cout << world_rank << " received ping_pong_count " 
                << ping_pong_count << " from " << partner_rank << std::endl;
        }
    }
    MPI_Finalize();
    return 0;
}
