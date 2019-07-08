#include "mpi.h"
#include <iostream>

// mpiexec -n 8 mpi_hello
int main() {
    // ��ʼ�� MPI ����
    MPI_Init(NULL, NULL);

    // ͨ���������·������õ����п��Թ����Ľ�������
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // �õ���ǰ���̵���
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // �õ���ǰ���̵�����
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // ��ӡһ�����е�ǰ�������֣����Լ�
    // ���� communicator �Ĵ�С�� hello world ��Ϣ��
    std::cout << "Hello world from processor " << processor_name << ", rank " 
        << world_rank << " out of " << world_size << " processors" << std::endl;

    // �ͷ� MPI ��һЩ��Դ
    MPI_Finalize();
    return 0;
}