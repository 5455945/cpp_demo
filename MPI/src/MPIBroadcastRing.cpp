//������MPI�Ĵ����ݸ����ܼ��㵼�ۡ�
// Frank Nielsen ��ΰ���� 2018��7�µ�һ���һ��ӡˢ
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// filename: MPIBroadcastRing.cpp
// Broadcasting on the oriented ring
# include "mpi.h"
# include <cstdio>
# include <cstdlib>
using namespace std;

int next()
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    return ((rank + 1) % size);
}

int previous()
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    return ((size + rank - 1) % size);
}
// mpiexec MPIBroadcastRing.exe
int main(int argc, char* argv[]) {
    int rank, value, size;
    if (argc == 2)
        value = atoi(argv[1]);
    else
        value = rand() % 1001;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        // Master Node sends out the value
        MPI_Send(&value, 1, MPI_INT, next(), 0, MPI_COMM_WORLD);
    }
    else {
        // Slave Nodes block on receive then send on the value
        MPI_Recv(&value, 1, MPI_INT, previous(), 0, MPI_COMM_WORLD, &status);
        if (rank < size - 1) {
            MPI_Send(&value, 1, MPI_INT, next(), 0, MPI_COMM_WORLD);
        }
        printf("process %d received %d \n", rank, value);
    }
    MPI_Finalize();
    return 0;
}
// ���н��
//```
//mpiexec MPIBroadcastRing.exe
//process 5 received 41
//process 2 received 41
//process 3 received 41
//process 4 received 41
//process 1 received 41
//process 6 received 41
//process 7 received 41
//```
