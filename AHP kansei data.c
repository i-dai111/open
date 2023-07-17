#include <stdio.h>
#include <math.h>
#define N 16
#define K 10000

int main(void) {

double a[N][N]={{11.0,0.0,0.0,3.0,0.0,0.0,5.0,0.0,0.0,3.0,0.0,0.0,1.0,0.0,0.0,1.0},
{0.0,11.0,0.0,1.0,0.0,0.0,5.0,0.0,0.0,3.0,0.0,0.0,1.0,0.0,0.0,1.0},
{0.0,0.0,11.0,1.0,0.0,0.0,3.0,0.0,0.0,1.0/3.0,0.0,0.0,1.0/3.0,0.0,0.0,1.0/3.0},
{1.0/3.0,1.0,1.0,9.0,0.0,0.0,3.0,0.0,0.0,1.0/3.0,0.0,0.0,1.0/3.0,0.0,0.0,1.0/3.0},
{0.0,0.0,0.0,0.0,12.0,0.0,1.0,0.0,0.0,1.0/3.0,0.0,0.0,1.0/5.0,0.0,0.0,1.0/3.0},
{0.0,0.0,0.0,0.0,0.0,12.0,1.0,0.0,0.0,1.0/3.0,0.0,0.0,1.0/5.0,0.0,0.0,1.0},
{1.0/5.0,1.0/5.0,1.0/3.0,1.0/3.0,1.0,1.0,7.0,0.0,0.0,1.0,0.0,0.0,1.0/5.0,0.0,0.0,1.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,13.0,0.0,1.0/3.0,0.0,0.0,1.0/5.0,0.0,0.0,1.0/3.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,13.0,1.0/3.0,0.0,0.0,1.0/7.0,0.0,0.0,1.0/5.0},
{1.0/3.0,1.0/3.0,3.0,3.0,3.0,3.0,1.0,3.0,3.0,5.0,0.0,0.0,1.0/3.0,0.0,0.0,1.0/3.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,14.0,0.0,1.0,0.0,0.0,5.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,14.0,1.0,0.0,0.0,5.0},
{1.0,1.0,3.0,3.0,5.0,5.0,5.0,5.0,7.0,3.0,1.0,1.0,3.0,0.0,0.0,1.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,15.0,0.0,1.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,15.0,1.0},
{1.0,1.0,3.0,3.0,3.0,1.0,1.0,3.0,5.0,3.0,1.0/5.0,1.0/5.0,1.0,1.0,1.0,1.0}},x[N],x_new[N],x_old[N],u[N],vector,max;

int i=0,j=0,count=0;

int k=0;

while(1){
	for(i=0;i<N;i++){
	x_old[i]=a[count][i];
	}
	
	for(k=0;k<K;k++){
		vector=0.0;
  	for(i=0;i<N;i++){
	 	 vector=vector+x_old[i]*x_old[i];
  	}
  	vector=sqrt(vector);
  	for(i=0;i<N;i++){
	  	u[i]=x_old[i]/vector;
  	}
  	for(i=0;i<N;i++){
			x_new[i]=0.0;
	  	for(j=0;j<N;j++){
		  	x_new[i]=x_new[i]+a[i][j]*u[j];
	  	}
  	}
		max=0.0;
		for(i=0;i<N;i++){
			if(max<fabs(x_old[i]-x_new[i])){
		  	max=fabs(x_old[i]-x_new[i]);
			}
		}
		j=0;
		if(max<0.0000001){
			j=1;
		}else{
			for(i=0;i<N;i++){
				x_old[i]=x_new[i];
			}
		}
		
	if(j==1){
		break;
	}
}
	if(j==1){
		break;
	}
	count++;
}

	
printf("%f\n",vector);
for(i=0;i<N;i++){
		printf("%f\n",u[i]);
}

return 0;
}