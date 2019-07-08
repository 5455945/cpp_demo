#include "mpi.h"
#include <cassert>
#include <iostream>

// https://mpitutorial.com/tutorials/mpi-broadcast-and-collective-communication/zh_cn/
// mpiexec -n 2 mpi_compare_bcast 100000 10
// mpiexec -n 16 mpi_compare_bcast 100000 10
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
    if (argc != 3) {
        //fprintf(stderr, "Usage: compare_bcast num_elements num_trials\n");
        std::cerr << "Usage: compare_bcast num_elements num_trials" << std::endl;
        return 1;
    }

    int num_elements = atoi(argv[1]);
    int num_trials = atoi(argv[2]);

    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    double total_my_bcast_time = 0.0;
    double total_mpi_bcast_time = 0.0;
    int i;
    int* data = (int*)malloc(sizeof(int) * num_elements);
    assert(data != NULL);

    for (i = 0; i < num_trials; i++) {
        // Time my_bcast
        // Synchronize before starting timing
        MPI_Barrier(MPI_COMM_WORLD);
        total_my_bcast_time -= MPI_Wtime();
        my_bcast(data, num_elements, MPI_INT, 0, MPI_COMM_WORLD);
        // Synchronize again before obtaining final time
        MPI_Barrier(MPI_COMM_WORLD);
        total_my_bcast_time += MPI_Wtime();

        // Time MPI_Bcast
        MPI_Barrier(MPI_COMM_WORLD);
        total_mpi_bcast_time -= MPI_Wtime();
        MPI_Bcast(data, num_elements, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        total_mpi_bcast_time += MPI_Wtime();
    }

    // Print off timing information
    if (world_rank == 0) {
        //printf("Data size = %d, Trials = %d\n", num_elements * (int)sizeof(int),
        //    num_trials);
        //printf("Avg my_bcast time = %lf\n", total_my_bcast_time / num_trials);
        //printf("Avg MPI_Bcast time = %lf\n", total_mpi_bcast_time / num_trials);
        std::cout << "Data size = " << num_elements * (int)sizeof(int) 
            << ", Trials = " << num_trials << std::endl;
        std::cout << "Avg my_bcast time = " << total_my_bcast_time / num_trials << std::endl;
        std::cout << "Avg MPI_Bcast time = " << total_mpi_bcast_time / num_trials << std::endl;
    }

    free(data);
    MPI_Finalize();

    return 0;
}
