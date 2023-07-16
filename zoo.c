#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#define N 256 // 1行の最大文字数(バイト数)


//nは個数 mは次元数 Cは何個のクラスターに分けるか
int main(void) {
	int n=101,m=16;
	int C=3;
  float X[n][m];//データ
	int i,j,k;
	double term=1;
	double theta=2;//Θ
	double XXXX;


	FILE *fp; // FILE型構造体
	char fname[] = "zoo.txt";
	char line[N];
	char str[16];
 

 
	fp = fopen(fname, "r"); // ファイルを開く。失敗するとNULLを返す。
	if(fp == NULL) {
		printf("%s file not open!\n", fname);
		return -1;
	}
 i=0;
	while(fgets(line, N, fp) != NULL) {
		sscanf(line, "%[^,],%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", str, &X[i][0], &X[i][1], &X[i][2], &X[i][3], &X[i][4], &X[i][5], &X[i][6], &X[i][7], &X[i][8], &X[i][9], &X[i][10], &X[i][11], &X[i][12], &X[i][13], &X[i][14], &X[i][15], &XXXX);
 i++;

	}
 
	fclose(fp); // ファイルを閉じる

	


	int ZZ=100;
	double u[C][n];//メンバシップ
	double ut[C][n];//メンバシップのΘ乗
	double utsum[C];//utの合計
	double usum[n];//uの合計列ごと
	double b[C][m];//クラスター中心
	double d[C][n];//距離
	double u_old[C][n];//break用
	double bbb[ZZ*C][m];
	for(int Z=0;Z<ZZ;Z++){
		srand((unsigned)time(NULL));
		for(k=0;k<C;k++){
			for(i=0;i<n;i++){
		 	u[k][i]= (double)rand()/RAND_MAX;
		 	u_old[k][i]=0;
			}
		}
		sleep(1);
	
		for(k=0;k<n;k++){
			usum[k]=0;
		}//usumを0に
		for(k=0;k<C;k++){
			for(i=0;i<n;i++){
				usum[i]+=u[k][i];
			}//usumに
		}
		for(k=0;k<C;k++){
			for(i=0;i<n;i++){
				u[k][i]/=usum[i];
			}
		}

//ここまで準備
		for(int ii=0;ii<100;ii++){
			for(k=0;k<C;k++){
				for(i=0;i<n;i++){
					ut[k][i] = pow(u[k][i],theta);
				}
			}
			for(k=0;k<C;k++){
				utsum[k]=0;
			}
			for(k=0;k<C;k++){
				for(i=0;i<n;i++){
					utsum[k]=utsum[k]+ut[k][i];
				}
			}
			for(i=0;i<C;i++){
				for(j=0;j<m;j++){
					b[i][j] = ut[i][j] * X[i][j];
					// 行列の項を計算
					for(i=0;i<C;i++){
						for(j=0;j<m;j++){
							term = 0.0;
							for(k=0;k<n;k++)
								term = term + ut[i][k]*X[k][j];
							b[i][j] = term;
						}
					}
				}
			}
			for(i=0;i<C;i++){
				for(j=0;j<m;j++){
					b[i][j]=b[i][j]/utsum[i];
				}
			}
			for(i=0;i<C;i++){
				for(j=0;j<n;j++){
					d[i][j]=0;
				}
			}
			for(i=0;i<C;i++){
				for(j=0;j<n;j++){
					for(k=0;k<m;k++){
						d[i][j]+=pow(b[i][k]-X[j][k],2);
					}
				}
			}
			for(i=0;i<C;i++){
				for(j=0;j<n;j++){
					d[i][j]=sqrt(d[i][j]);
				}
			}

			for(i=0;i<C;i++){
				for(j=0;j<n;j++){
					u[i][j]=pow(d[i][j],(2/(1-theta)));
				}
			}

			for(k=0;k<n;k++){
				usum[k]=0;
			}//usumを0に
			for(k=0;k<C;k++){
				for(i=0;i<n;i++){
					usum[i]+=u[k][i];
				}//usumに
			}
			for(k=0;k<C;k++){
				for(i=0;i<n;i++){
					u[k][i]/=usum[i];
				}
			}

			term=0;
			for(k=0;k<C;k++){
				for(i=0;i<n;i++){
					if(fabs(u[k][i]-u_old[k][i])>term){
						term=fabs(u[k][i]-u_old[k][i]);
					}
				}
			}

			if(term<=1e-5)
				break;
			for(k=0;k<C;k++){
				for(i=0;i<n;i++){
					u_old[k][i]=u[k][i];
				}
			}


	
		}

		for(k=0;k<C;k++){
			for(i=0;i<m;i++){
				bbb[(Z*C)+k][i]=b[k][i];
			}
		}
	}
	for(k=0;k<ZZ*C;k++){
		for(i=0;i<m;i++){
				if(i!=0){
					printf(",");
				}
			printf("%f",bbb[k][i]);
		}
		printf("\n");
	}

	
	for(k=0;k<ZZ*C;k++){
		bbb[k][12]=bbb[k][12]/8;
	}
	fopen("rresult8.csv", "w");

	//	全部１から0にした場合
	for(k=0;k<ZZ*C;k++){
		for(i=0;i<m;i++){
				if(i!=0){
					fprintf(fp,",");
				}
			fprintf(fp,"%f",bbb[k][i]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);


	return 0;
}