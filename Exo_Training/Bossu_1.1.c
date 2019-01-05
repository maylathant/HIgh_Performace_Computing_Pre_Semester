#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#ifndef max
    #define max(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define CHUNKSIZE   10
#define N       10000000

double drand()   /* uniform distribution, (0..1] */
{
  return (rand()+1.0)/(RAND_MAX+1.0);
}
double random_normal()  /* normal distribution, centered on 0, std dev 1 */
{
  return sqrt(-2*log(drand())) * cos(2*M_PI*drand());
}

double getPath(int per, double vol, double S0, double C){


  int i,j;
  double z, St=S0, tsteps = 2;
  double h = 1/tsteps;

    for(i = 1; i<=per; i++){
        for(j = 1; j<=tsteps; j++){
          z = random_normal();
          St = St*exp(-vol*vol*0.5*h + vol*sqrt(h)*z);
        }
        //Determine if called
        if(St > S0 && i < per){return 1.0 + i*C;}
    }

    //Check terminal payout at final time
    if(St > 0.7*S0){
      return max(1+per*C,St/S0);
    }

   return St/S0;

}

int main (int argc, char *argv[])
{
    double x, S0 = 100, vol = 0.25, C = 0.075675, price = 0.0;
    int per = 3, chunk = CHUNKSIZE, p;


    //Start clock
    double begin = omp_get_wtime();

    //Initialize Random numbers
    srand(time(NULL)); 

    //Take the Average of many paths
    #pragma omp parallel shared(per,vol,S0,C,chunk)
    {
    #pragma omp for schedule(static,chunk) reduction(+:price)
      for(p = 1; p<=N; p++){price += getPath(per,vol,S0,C);}
    }
    
    printf("The Price is: %f\n", price/N);
    //End CLock
    double end = omp_get_wtime();
    double time_spent = (end - begin);

    printf("Time Spent: %f\n", time_spent);

    return 0;
}