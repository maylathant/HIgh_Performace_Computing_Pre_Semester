#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main (int argc, char *argv[])
{
    double integral, delta, x;
    int i, N = 100000;
    delta = 1.0/N;
    integral = 0.0;

    //Start clock
    clock_t begin = clock();

    #pragma omp parallel shared(integral) private(i,x)
    {
        #pragma omp for reduction(+:integral)
        for(i=1;i<=N;i++){
            //#pragma omp critical
            x = i*delta;
            integral += delta*sqrt(1 - x*x);
            if (i%1000 == 0){
                //printf("Integral is %f for i = %d current box is %f\n", integral,i,delta);
            }

            //Increment evaluation point
            
        }
    }

    //End CLock
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("pi Approximation is %f. Time Spent: %f \n", 4.0*integral,time_spent);

    return 0;
}