#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int binaryFunc(int *args, int binfin(int x, int y)){
	return binfin(args[0],args[1]);
}

int subtract(int x, int y){
	return x - y;
}

//Define 2-norm
double norm2(double *x,int len){

	double result = 0;
	for(int i = 0; i < len; i++){result += x[i]*x[i];}
	return sqrt(result);

}

//Define 1 norm
double norm1(double *x,int len){

	double result = 0;
	for(int i = 0; i < len; i++){result += fabs(x[i]);}
	return result;

}

//Compute arbitrarily defined norm
//array x, function pointer norm to define norm
double getNorm(double *x,int len,double norm(double *v, int s)){
	return norm(x,len);
}

int main(){

	//Declare and initalize array
	int size = 4;

	double *arr = malloc(sizeof(double)*size);

	for(int i=0;i<size;i++){arr[i]=2.0;}

	//Select function pointer
	double (*fun_ptr)(double*,int) = &norm2;
	
	printf("Result is %f\n", getNorm(arr,size,fun_ptr));
	return 0;
}