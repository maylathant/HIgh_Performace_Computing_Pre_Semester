#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char* argv[])
{

int numprocs, myid, resultlength,partner,buf,message,count =1;
char name[MPI_MAX_PROCESSOR_NAME];

MPI_Status Stat;

/* MPI Initialization */
MPI_Init (&argc, &argv);
MPI_Get_processor_name (name,&resultlength);
MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
MPI_Comm_rank (MPI_COMM_WORLD, &myid);

if (myid < numprocs/2){partner = numprocs/2 + myid;}
else if (myid >= numprocs/2){ partner = myid - numprocs/2;}

buf = myid+5;



if (myid < numprocs/2) {
     partner = numprocs/2 + myid;
     MPI_Send (&buf,count,MPI_INT,partner,1,MPI_COMM_WORLD);
     MPI_Recv (&message,count,MPI_INT,partner,1,MPI_COMM_WORLD,&Stat);
     }
   else if (myid >= numprocs/2) {
     partner = myid - numprocs/2;
     MPI_Recv (&message,count,MPI_INT,partner,1,MPI_COMM_WORLD,&Stat);
     MPI_Send (&buf,count,MPI_INT,partner,1,MPI_COMM_WORLD);
     }

printf("Hello, I am %d and my partner is %d who sent me %d\n",myid,partner,message);

MPI_Finalize();
}   