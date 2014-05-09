#include <stdio.h>
#include <stdlib.h>

#define N 1000
double soma_array(double a[N][N]);

int main ( int argc , char * argv [] ) {

   double a[N][N];
   int i, j;

   // preenche vetores com valores aleatorios de 0 a 999
   for ( j = 0 ; j < N ; j ++) {
      for ( i = 0 ; i < N ; i ++) {
         a[i][j] = 0.01;
	  }
   }

   printf("soma = %10.3f\n", soma_array(a));

   return 0;
}

double soma_array(double a[N][N]){

   double s=0;
   int i, j;
   for (i = 0; i < N; i = i++){
     for (j = 0; j < N; j++){
        s += a[i][j];
	  }
   }
   return s;
}
