#include "mpi.h"
#include <iostream>

// https://mpitutorial.com/tutorials/mpi-broadcast-and-collective-communication/zh_cn/
// mpiexec -n 4 mpi_my_bcast
void my_bcast(void* data, int count, MPI_Datatype datatype, int root,
    MPI_Comm communicator) {
    int world_rank;
    MPI_Comm_rank(communicator, &world_rank);
    int world_size;
    MPI_Comm_size(communicator, &world_size);

    if (world_rank == root) {
        // If we are the root process, send our data to everyone
        int i;
        for (i = 0; i < world_size; i++) {
            if (i != world_rank) {
                MPI_Send(data, count, datatype, i, 0, communicator);
            }
        }
    }
    else {
        // If we are a receiver process, receive the data from the root
        MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
    }
}

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int data;
    if (world_rank == 0) {
        data = 100;
        //printf("Process 0 broadcasting data %d\n", data);
        std::cout << "Process 0 broadcasting data " << data << std::endl;
        my_bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    else {
        my_bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
        //printf("Process %d received data %d from root process\n", world_rank, data);
        std::cout << "Process " << world_rank << " received data " 
            << data << " from root process" << std::endl;
    }

    MPI_Finalize();

    return 0;
}
