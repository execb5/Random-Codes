#include<stdlib.h>
int main(){
   float *p, *a;
   p = malloc(10*sizeof(float));
   a = malloc(10*sizeof(float));
   a[3] = p[3];
   free(a);
   free(p);
}
