#include <iostream>
#include <ctime>        
#include <cstdlib>      
#include<string>
using namespace std;
#define NUM_CARDS 52 // トランプ1組のカード枚数
#define NUM_ATTRIBUTES 2 // ゲームに関わる人数 (プレイヤとディーラ)
enum ATTRIBUTE { // プレイヤとディーラの区別用
PLAYER, 
DEALER
};
class Blackjack {
protected:
// 引いたカードのマーク (S:スペード, H:ハート, D:ダイヤ, C:クラブ) と番号を格納
// 1番目の配列要素でプレイヤとディーラ，
// 2番目の配列要素で引いた各カードを区別 (カードは最大11枚まで引ける)
char mark[NUM_ATTRIBUTES][11]; 
int number[NUM_ATTRIBUTES][11];
// プレイヤとディーラが既に引いたカードの枚数を格納
// 配列要素でプレイヤとディーラを区別
// プレイヤがカードを2枚引き終えると num_cards_drawn[PLAYER] == 2，
// 3枚引き終えると num_cards_drawn[PLAYER] == 3 のように更新されていく
int num_cards_drawn[NUM_ATTRIBUTES]; 
// 当該カードが既に引かれているか (0:引かれてない, 1:引かれている)
int drawn[NUM_CARDS];

public:
Blackjack(char _mark[NUM_ATTRIBUTES][11],int _number[NUM_ATTRIBUTES][11], int _num_cards_drawn[NUM_ATTRIBUTES], int _drawn[NUM_CARDS]){ // コンストラクタ (各データメンバの初期化が必要)
	for(int i=0;i<NUM_ATTRIBUTES;i++){
		for(int j=0;j<11;j++){
mark[i][j]=_mark[i][j];
number[i][j]=0;
			}
		num_cards_drawn[i]=0;
		}
for(int i=0;i<NUM_CARDS;i++){
	drawn[i]=0;
}
}
	
// ディーラとプレイヤがそれぞれ最初の2枚のカードを引く (講義資料p.6の処理1)
void init_action(){
	draw_card(PLAYER);
	draw_card(PLAYER);
	draw_card(DEALER);
	draw_card(DEALER);
	cout<<"DEALER "<<mark[DEALER][0]<<number[DEALER][0]<<"   ***"<<endl;
	print_cards(PLAYER);
}
// プレイヤがHitかStandを決める (講義資料p.6の処理2)
// 返り値として，2-bに該当する場合に0，2-a-bに該当する場合に1をそれぞれ返し，
// 値が返された後の分岐処理はmain関数で行うことを想定
int player_action(){
	string s;

cout<<"Hit(h) or Stand(s)?";
	cin>>s;
	
	if(s=="h"){
		draw_card(PLAYER);
		print_cards(PLAYER);
		if(sum_cards(PLAYER)>21){return 1;}else{return 2;}
		}else if(s=="s"){
		return 0; 
		}else{return 1;}
			}
	
// ディーラがカードを引く (講義資料p.7の処理3)
// 返り値として，3-bに該当する場合に0，3-a-bに該当する場合に1をそれぞれ返し，
// 値が返された後の分岐処理，および講義資料p.7の処理4はmain関数で行うことを想定
int dealer_action(){
		if(sum_cards(DEALER)<17){
			draw_card(DEALER);
			if(sum_cards(DEALER)<22){
				return 2;
			}else if(sum_cards(DEALER)>22){
				print_cards(DEALER);
				return 1;
			}
		}else{
			print_cards(DEALER);
			return 0;}
	}

// 以下のメンバ関数は，処理対象（プレイヤかディーラ）を引数で指定
// 例: ディーラがカードを引く処理は draw_card(DEALER) で実行
// カードを1枚自動で引く
// 引いたカードはデータメンバのmarkとnumberに2番目の配列要素値が小さい順に
// 格納していく

void draw_card(ATTRIBUTE attr){

int x,i=0;
srand(time(NULL));
do{
	
	x=rand()%NUM_CARDS;
}while(drawn[x]==1);
	drawn[x]=1;
	number[attr][num_cards_drawn[attr]]=(x%13)+1;
x=x%4;
			switch(x){
				case 0:mark[attr][num_cards_drawn[attr]]='S';break;
				case 1:mark[attr][num_cards_drawn[attr]]='H';break;
				case 2:mark[attr][num_cards_drawn[attr]]='D';break;
				case 3:mark[attr][num_cards_drawn[attr]]='C';break;
			}
	num_cards_drawn[attr]++;

	}
		

// 引いた全カードの合計値を計算
int sum_cards(ATTRIBUTE attr){
	int sum=0,i;
	for (i=0;i<11;i++){
		if(number[attr][i]>10){
			sum=sum+10;
			}else{
		sum=sum+number[attr][i];
			}
	}
	return sum;
}
// 引いた全てのカードを表示
void print_cards(ATTRIBUTE attr){
	int i;
	if(attr==DEALER){
	cout<<"Dealer"<<"  ";
		}else{cout<<"Player"<<"  ";}
	
	for(i=0;i<num_cards_drawn[attr];i++){
		
			cout<<mark[attr][i]<<number[attr][i]<<"   ";

	}
cout<<endl;

}
int last_sum_cards(ATTRIBUTE attr){
		int sum=0,i;
	for (i=0;i<11;i++){
		if(number[attr][i]>10){
			sum=sum+10;
			}else{
		sum=sum+number[attr][i];
			}
		}
	for(int i=0;i<11;i++){
		if(number[attr][i]==1&&sum<11){
			sum=sum+10;
		}
	}

	return sum;
}

}; // class Blackjack

int main (void){
	char mmark[NUM_ATTRIBUTES][11];
	int mnumber[NUM_ATTRIBUTES][11];
	int mnum_cards_drawn[NUM_ATTRIBUTES];
	int mdrawn[NUM_CARDS];
	int p,d,psum,dsum;

	for(int i=0;i<NUM_ATTRIBUTES;i++){
		for(int j=0;j<11;j++){
mmark[i][j]='s';
mnumber[i][j]=0;
			}
		mnum_cards_drawn[i]=0;
		}
for(int i=0;i<NUM_CARDS;i++){
	mdrawn[i]=0;
}

	
	Blackjack bl(mmark,mnumber,mnum_cards_drawn,mdrawn);

	bl.init_action();
	do{
p=bl.player_action();
		}while(p==2);
	psum=bl.last_sum_cards(PLAYER);
	
	if(p==1){
		cout<<"Player lose (Player"<<psum<<", Dealer"<<bl.sum_cards(DEALER)<<") (Player Bust)";
	}else if(p==0){

	do{
d=bl.dealer_action();
		}while(d==2);

dsum=bl.last_sum_cards(DEALER);
	
		if(d==1){
				cout<<"Player win (Player"<<psum<<", Dealer"<<dsum<<") (Dealer Bust)";	
		}else if(d==0){
			if(psum>dsum){
								cout<<"Player win (Player"<<psum<<", Dealer"<<dsum<<")";
			}else if(psum<dsum){
						cout<<"Player lose (Player"<<psum<<", Dealer"<<dsum<<")";
		}else if(psum==dsum){
					cout<<"Push (Player"<<psum<<", Dealer"<<dsum<<")";
		}

			}
		}
	
}