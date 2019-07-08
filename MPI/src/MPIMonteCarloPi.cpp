//《基于MPI的大数据高性能计算导论》
// Frank Nielsen 张伟哲译 2018年7月第一版第一次印刷
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// filename: MPIMonteCarloPi.cpp
#include "mpi.h"
#include <cassert>
#include <ctime>
#include <iostream>
// mpiexec MPIMonteCarloPi.exe
#define random() (rand() / double (RAND_MAX) * 2 - 1)

int main(int argc, char** argv) {
    int comm_sz;
    int my_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    long long int count_time; // 总的计算次数
    long long int Cal[2] = { 0 };
    if (my_rank == 0) {
        count_time = 10000000;
        long long int tempCal[2] = { 0 };
        assert(comm_sz > 1);
        long long int width = count_time / (comm_sz - 1);
        long long int reminder = count_time % (comm_sz - 1);
        long long int temp_count_time;
        for (int i = 1; i < comm_sz; ++i)
        {
            temp_count_time = width;
            if (i <= reminder) temp_count_time++;
            MPI_Send(&temp_count_time, 1, MPI_LONG_LONG_INT, i, 0, MPI_COMM_WORLD);
        }
        for (int i = 1; i < comm_sz; ++i)
        {
            MPI_Recv(tempCal, 2, MPI_LONG_LONG_INT, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
            for (int j = 0; j < 2; ++j) { Cal[j] += tempCal[j]; }
        }

        std::cout << 4.0 * Cal[0] / count_time << std::endl;
    } // 运算的子节点
    else {
        srand((unsigned)time(NULL));
        MPI_Recv(&count_time, 1, MPI_LONG_LONG_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        Cal[1] = count_time;
        Cal[0] = 0;
        double x, y, dst;
        for (int i = 0; i < count_time; ++i) {
            x = random();
            y = random();
            dst = x * x + y * y;
            if (dst <= 1) Cal[0] += 1;
        }
        MPI_Send(Cal, 2, MPI_LONG_LONG_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();

    return 0;
}
// 运行结果
//```
//mpiexec MPIMonteCarloPi.exe
//3.13993
//```
