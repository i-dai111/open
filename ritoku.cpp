#include <iostream>
#include <vector>
#include <cmath>
#include<stdio.h>
#include <chrono>
#include <time.h>  




using namespace std;

  /*double a[number] = {3, 5, 4, 2, 10, 7, 1, 5, 6, 8, 9, 15, 12, 14, 13, 11, 4, 6, 11, 3, 3, 5, 8, 14, 9, 10, 2, 1, 13, 7, 6, 15};*/
  /*double c[number] = {3, 7, 6, 3, 13, 9, 2, 6, 11, 11, 9, 18, 19, 21, 13, 15, 5, 7, 16, 5, 3, 6, 15, 19, 12, 15, 4, 1, 18, 10, 8, 18};*/

int main(void){
vector <vector <double>> kumiawase={{6,15},{3,4},{4,10},{8,9},{1,1},{3,8},{9,11},{2,2},{7,18},{4,11},{9,21},{15,16},{12,19},{14,15},{13,14},{11,11},{1,1},{6,16},{2,5},{5,6},{3,3},{7,17},{8,10},{14,15},{12,12},{10,11},{2,5},{10,12},{13,15},{7,17},{6,16},{15,16}};

int y=16;//データの数
int sou=pow(2,y);//すべての組み合わせの合計数
	int k;
	int max=0;//利得の最大値
	int count;
	int size;
	int x;
	int youryou=25;
	unsigned long s=sou;
	vector <vector <int>> kumi{s};//組み合わせのデータ保管
	vector <vector <int>> yr(s, vector<int>(2,0));;//容量と利得　左が容量　右が利得
  double time=0;
double average=0;
double bunnsann=0;
double kachi[y];


		
 std::chrono::system_clock::time_point  start, end; // 型は auto で可
 start = std::chrono::system_clock::now(); // 計測開始時間



	
//全体的なイメージとしては10進数を二進数に直して、そのビットが1の時のみ
//そのビットに割り振ったと想定している製品を入れる
	for(int i=0;i<pow(2,y);i++){//2の製品数乗ループ
		k=i;//iをkに代入
		for(int j=0;j<y;j++){

			x=k%2;//xはkを2で割った余り
			if(x==1){//もし1余りなら入れる
				yr[i][0]=kumiawase[j][0]+yr[i][0];
				yr[i][1]=kumiawase[j][1]+yr[i][1];
				kumi[i].push_back(j+1);
			
				}
			k=k/2;//kを半分にする
			}
	
	}
	for(int i=0;i<pow(2,y);i++){
		if(yr[i][0]<=youryou){
			if(max<yr[i][1]){
			max=yr[i][1];
		count=i;
				}
			}
	}



	size=kumi[count].size();
	

 end = std::chrono::system_clock::now();  // 計測終了時間
 double elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count(); //処理に要した時間をミリ秒に変換

	cout<<"time  "<<elapsed<<endl;
cout<<"入れた番号は";
	for(int i=0;i<size;i++){
	cout<<kumi[count].at(i)<<"  ";
		}
	cout<<endl<<"容量は"<<yr[count][0]<<"   利得は"<<yr[count].at(1)<<endl;




  return 0;
}