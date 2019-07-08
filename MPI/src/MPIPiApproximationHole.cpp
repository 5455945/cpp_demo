//《基于MPI的大数据高性能计算导论》
// Frank Nielsen 张伟哲译 2018年7月第一版第一次印刷
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// filename: MPIPiApproximationHole.cpp
#include "mpi.h"
#include <iostream>
// mpiexec MPIPiApproximationHole.exe
int main(int argc, char** argv) {
    int n, rank, size, i;
    double PI = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    while (1) {
        if (rank == 0) {
            std::cout << "Enter n (or an integer < 1 to exit) :" << std::endl;
            std::cin >> n;
        }

        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (n < 1) {
            break;
        }
        else {
            h = 1.0 / (double)n;
            sum = 0.0;
            for (i = rank + 1; i <= n; i += size) {
                x = h * ((double)i - 0.5);
                sum += (4.0 / (1.0 + x * x));
            }
            mypi = h * sum;

            MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_PROD, 0, MPI_COMM_WORLD);
            if (rank == 0) {
                std::cout << "pi is approximated by " << pi
                    << ", the error is " << fabs(pi - PI) << std::endl;
            }
        }
    }
    MPI_Finalize();
    return 0;
}
