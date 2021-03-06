#include <stdio.h>
#include <omp.h>

#define N 10
#define M 10

double Uold[N][M];
double Unew[N][M];
double x[N];
double y[M];
int i,j,k;

void printU(){
	for(int i=0;i<N; i++){
		for (int j=0; j<M; j++){
			printf("%f ",Unew[i][j]);
		}
		printf("\n");
	}
}


void func(){
	for(int i=1;i<(N-1); i++){
		for(int j=1; j<(M-1); j++){
			Unew[i][j]=(Uold[i+1][j]+Uold[i-1][j]+Uold[i][j+1]+Uold[i][j-1]-(x[i]*x[i]+y[i]*y[i]))/4;
//		printf("Unew[%d][%d]= %f\n",i,j,Unew[i][j]);
		}
	}
}

int main() {
	for(i=0;i<N; i++){
		for (j=0; j<M; j++){
			Uold[i][j]=1;
			Unew[i][j]=1;
		}
		x[i]=i*(1.0/N);
		y[i]=i*(1.0/M);
	}

#pragma omp parallel shared(x,y,Uold,Unew) private(k,i,j) default(none)
{
	#pragma omp for collapse(2)
	for(int i=1;i<(N-1); i++){
		for(int j=1; j<(M-1); j++){
			Unew[i][j]=(Uold[i+1][j]+Uold[i-1][j]+Uold[i][j+1]+Uold[i][j-1]-(x[i]*x[i]+y[i]*y[i]))/4;
//		printf("Unew[%d][%d]= %f\n",i,j,Unew[i][j]);
		}
	}
}


/*for(int k=0;k<5;k++){
	func();
}
*/
printU();
return 0;
}