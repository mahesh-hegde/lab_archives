#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openmpi/mpi.h>

#define BUF 64

int main(int argc, char **argv) {
	int rank, nprocs = 3, dest;
	int tag = 0;
	int root = 0;
	char message[BUF];
	MPI_Init(&argc, &argv);
	MPI_Status status;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	if (rank == 0) {
		printf("Total processes: %d\n", nprocs);
		strcpy(message, "Oiiii");
		for (int i = 1; i < nprocs; i++) {
			MPI_Send(message, BUF, MPI_CHAR, i, tag, MPI_COMM_WORLD);
		}
	} else {
		MPI_Recv(message, BUF, MPI_CHAR, root, tag, MPI_COMM_WORLD, &status);
		printf("%s in p(%d) from p(%d)\n", message, rank, root);
	}
	MPI_Finalize();
}
