#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define VECLEN 100

float a[VECLEN], b[VECLEN], sum;



int main (int argc, char *argv[]) {
int p,t,m,n,d;

p = omp_get_max_threads();


int i;
double sum;

int in, out;

#pragma omp parallel
{
  for (i=0; i < VECLEN; i++)
    a[i] = b[i] = 1.0 * i;
  sum = 0.0;
  t = omp_get_num_threads();
  in = omp_in_parallel();
}

omp_set_nested(0);

out = omp_in_parallel();
m = omp_get_max_threads();
d = omp_get_dynamic();
n = omp_get_nested();


printf("Number of Processors %d\nNumber of Threads %d\n", p,t);
printf("Max Threads: %d\nIn Parellel?: %d\n", m,in);
printf("Nested Enabled: %d\nDynamic Enabled?: %d\n", n,d);

return 0;

}
