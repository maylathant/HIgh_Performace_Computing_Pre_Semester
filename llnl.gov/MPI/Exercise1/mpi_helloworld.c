#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char* argv[])
{

int numprocs, myid, resultlength;
char name[MPI_MAX_PROCESSOR_NAME];

/* MPI Initialization */
MPI_Init (&argc, &argv);
MPI_Get_processor_name (name,&resultlength);
MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
MPI_Comm_rank (MPI_COMM_WORLD, &myid);


if(myid == 0){printf("Hello, I am %d leading a team of %d tasks\n",myid,numprocs);}
else{printf("Hello, I am task %d running on processor %s\n",myid, name);}

MPI_Finalize();
}   