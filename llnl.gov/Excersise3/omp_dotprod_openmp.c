/*****************************************************************************
* FILE: omp_dotprod_serial.c
* DESCRIPTION:
*   This simple program is the serial version of a dot product and the
*   first of four codes used to show the progression from a serial program to a 
*   hybrid MPI/OpenMP program.  The relevant codes are:
*      - omp_dotprod_serial.c  - Serial version
*      - omp_dotprod_openmp.c  - OpenMP only version
*      - omp_dotprod_mpi.c     - MPI only version
*      - omp_dotprod_hybrid.c  - Hybrid MPI and OpenMP version
* SOURCE: Blaise Barney
* LAST REVISED:  06/02/17 Blaise Barney
******************************************************************************/

//Anthony Maylath 12/22/2018 ~ Alter for OpenMP

#include <stdio.h>
#include <stdlib.h>

/* Define length of dot product vectors */
#define VECLEN 100

int main (int argc, char* argv[])
{
int i,len=VECLEN;
double *a, *b;
double sum;

printf("Starting omp_dotprod_openmp\n");

/* Assign storage for dot product vectors */
a = (double*) malloc (len*sizeof(double));
b = (double*) malloc (len*sizeof(double));

#pragma omp parallel shared(len), private(i)
{ 
  /* Initialize dot product vectors */
  #pragma omp for
    for (i=0; i<len; i++) {
      a[i]=i + 0.0;
      b[i]=a[i];
      }
}

sum = 0.0;
#pragma omp parallel shared(len,sum), private(i)
{
  /* Perform the dot product */
  #pragma omp for reduction(+:sum)
    for (i=0; i<len; i++) 
      {
        sum += (a[i] * b[i]);
      }
}

printf ("Done. Openmp version: sum  =  %f \n", sum);

free (a);
free (b);
}   