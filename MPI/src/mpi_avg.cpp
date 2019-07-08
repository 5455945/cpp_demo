#include "mpi.h"
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <iostream>

// https://mpitutorial.com/tutorials/mpi-scatter-gather-and-allgather/zh_cn/
// mpiexec -n 4 mpi_avg 100

// Creates an array of random numbers. Each number has a value from 0 - 1
float* create_rand_nums(int num_elements) {
    float* rand_nums = (float*)malloc(sizeof(float) * num_elements);
    assert(rand_nums != NULL);
    int i;
    for (i = 0; i < num_elements; i++) {
        rand_nums[i] = (rand() / (float)RAND_MAX);
    }
    return rand_nums;
}

// Computes the average of an array of numbers
float compute_avg(float* array, int num_elements) {
    float sum = 0.f;
    int i;
    for (i = 0; i < num_elements; i++) {
        sum += array[i];
    }
    return sum / num_elements;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        //fprintf(stderr, "Usage: avg num_elements_per_proc\n");
        //exit(1);
        std::cerr << "Usage: avg num_elements_per_proc" << std::endl;
        return 1;
    }

    int num_elements_per_proc = atoi(argv[1]);
    // Seed the random number generator to get different results each time
    srand(time(NULL));

    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Create a random array of elements on the root process. Its total
    // size will be the number of elements per process times the number
    // of processes
    float* rand_nums = NULL;
    if (world_rank == 0) {
        rand_nums = create_rand_nums(num_elements_per_proc * world_size);
    }

    // For each process, create a buffer that will hold a subset of the entire
    // array
    float* sub_rand_nums = (float*)malloc(sizeof(float) * num_elements_per_proc);
    assert(sub_rand_nums != NULL);

    // Scatter the random numbers from the root process to all processes in
    // the MPI world
    MPI_Scatter(rand_nums, num_elements_per_proc, MPI_FLOAT, sub_rand_nums,
        num_elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Compute the average of your subset
    float sub_avg = compute_avg(sub_rand_nums, num_elements_per_proc);

    // Gather all partial averages down to the root process
    float* sub_avgs = NULL;
    if (world_rank == 0) {
        sub_avgs = (float*)malloc(sizeof(float) * world_size);
        assert(sub_avgs != NULL);
    }
    MPI_Gather(&sub_avg, 1, MPI_FLOAT, sub_avgs, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Now that we have all of the partial averages on the root, compute the
    // total average of all numbers. Since we are assuming each process computed
    // an average across an equal amount of elements, this computation will
    // produce the correct answer.
    if (world_rank == 0) {
        float avg = compute_avg(sub_avgs, world_size);
        //printf("Avg of all elements is %f\n", avg);
        std::cout << "Avg of all elements is " << avg << std::endl;

        // Compute the average across the original data for comparison
        float original_data_avg =
            compute_avg(rand_nums, num_elements_per_proc * world_size);
        //printf("Avg computed across original data is %f\n", original_data_avg);
        std::cout << "Avg computed across original data is " << original_data_avg << std::endl;
    }

    // Clean up
    if (world_rank == 0) {
        free(rand_nums);
        free(sub_avgs);
    }
    free(sub_rand_nums);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
