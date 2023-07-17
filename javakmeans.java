// ファイル読み込みのためのimport
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;



public class javakmeans {
	// 2次元配列を表示する関数
	public static void show(double[][] A) {
		for (int i = 0; i < A.length; i++) {
			for (int j = 0; j < A[0].length; j++) {
				System.out.print(A[i][j] + ", ");
			}
			System.out.println();
		}
	}

	// クラスター中心行列 b のランダム初期化
	// データ行列からC個の行を抽出し，初期クラスター中心行列 b を返す．
	public static double[][] b_init(double[][] X, int C) {
		// ここを適切に完成させる	
		double[][] b=new double[C][X[0].length];
		
		ArrayList<Integer> list = new ArrayList<Integer>();
		 for(int i = 0 ; i < X.length ; i++) {
            list.add(i);
        }
		Collections.shuffle(list);

		for(int i=0;i<C;i++){
			for(int j=0;j<X[0].length;j++){
				b[i][j]=X[list.get(i)][j];
			}
		}
		return b;
	}

	// 最近隣クラスターへの割り当て
	// クラスター中心行列 b とデータ行列 X から2乗距離行列dを算出し，
	// dを元にメンバシップ行列uを算出して返す．
	public static double[][] u_nearest(double[][] b, double[][] X) {
		// ここを適切に完成させる
int c=b.length;
int n=X.length;
int m=b[0].length;

double[][] u= new double[c][n];
double[][] d= new double[c][n];
//初期化
for(int i=0;i<c;i++){
	for(int j=0;j<n;j++){
		u[i][j]=0;
		d[i][j]=0;
	}
}
		//距離の計算
for(int i=0;i<n;i++){
	for(int j=0;j<c;j++){
for(int M=0;M<m;M++){
d[j][i]+=(X[i][M]-b[j][M])*(X[i][M]-b[j][M]);
}		
	}
}
		//距離が最小となるところを見つけuを１に		
for(int i=0;i<n;i++){
	int min=0;
	double dmin=d[0][i];
	for(int j=0;j<c;j++){
		if(dmin>d[j][i]){
			min=j;
			dmin=d[j][i];
		}
	}
	u[min][i]=1;
}
		return u;
	}

	// クラスター中心bの算出
	// メンバシップ行列 u とデータ行列 X から
	// 新しいクラスター中心 b を算出して返す．
	public static double[][] b_new(double[][] u, double[][] X) {
		// ここを適切に完成させる
int c=u.length;
int m=X[0].length;
int n=X.length;

double b[][]=new double[c][m];
double uci[]=new double[c];

		for(int i=0;i<c;i++){
			for(int j=0;j<m;j++){
				uci[i]=0;
			b[i][j]=0;	
		}
			}		
		
//クラスター容量の計算		
for(int i=0;i<c;i++){
	for(int j=0;j<n;j++){
		if(u[i][j]==1){
			uci[i]=uci[i]+1;
		}
	}
}
for(int i=0;i<c;i++){
	for(int j=0;j<m;j++){
		for(int k=0;k<X.length;k++){
b[i][j]+=u[i][k]*X[k][j];
	}
	}
}

for(int i=0;i<c;i++){
	for(int j=0;j<m;j++){
b[i][j]=b[i][j]/uci[i];
	}
}

		return b;
	}

	// 収束判定
	// u と u_old の差の絶対値によってクラスター割り当ての変化量を求める．
	// 変化がなければ true, そうでないなら false を返す．
	public static boolean convergence(double[][] u, double[][] u_old) {
		// ここを適切に完成させる
		int sa=0;
		for(int i=0;i<u.length;i++){
			for(int j=0;j<u[0].length;j++){
				sa+=Math.abs(u[i][j]-u_old[i][j]);
			}
		}
		if(sa==0){
			return true;
		}else{return false;}
	}

	public static void kmeans(double[][] X, int C) {
		int n = X.length;
		System.out.println("データ行列 X");
		show(X); // データ行列 X の表示
		double[][] u = new double[C][n]; // メンバシップ行列の宣言
		double[][] b = b_init(X, C); // 初期クラスター中心の設定
		System.out.println("初期クラスター中心 b");
		show(b); // 初期クラスター中心 b の表示
		for (int step = 0; step < 10; step++) {
			System.out.println("Step: " + step);
			double[][] u_old = u.clone(); // 前回のクラスター割り当て
			u = u_nearest(b, X); // 最近隣クラスターへの割り当て
			b = b_new(u, X); // クラスター中心bの算出
			if (convergence(u, u_old)) { // 収束判定
				break;
			}
		}
		System.out.println("クラスター割り当て u");
		show(u);
		System.out.println("クラスター中心 b");
		show(b);
	}

	public static void main(String[] args) {
		// 変数設定
		int n = 150; // 対象数 n
		int m = 4; // 次元数 m
		double[][] X = new double[n][m]; // データ行列 X の宣言
		// データの読込
		try {
			File file = new File("iris.data"); // ファイルのパスを指定する

			// BufferedReaderクラスのreadLineメソッドを使って1行ずつ読み込み表示する
			FileReader fileReader = new FileReader(file);
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			String row;

			// ここで X にデータを格納する (ここを適切に完成させる)
			// 何らかの処理
double [] idata=new double [X[0].length];
			int i=0;
			while ((row = bufferedReader.readLine()) != null) {
				// 何らかの処理
	 if ("".equals(row)) {

    }else{	
				
				String data= row.substring(0, 15);
			
			String[] sdata=data.split(",");	
				for(int j=0;j<X[0].length;j++){
					idata[j]=Double.parseDouble(sdata[j]);
				}
				for(int j=0;j<idata.length;j++){
					X[i][j]=idata[j];
				}
				i=i+1;
				}
			}
			fileReader.close(); // ファイルを閉じてリソースを開放する
		} catch (IOException e) { // 入出力例外発生時の処理
			e.printStackTrace(); // 標準エラー出力へ出力
		}

		// データ X に対し，クラスター数 C=3 として k-means法を実行．
		int C = 3;
		kmeans(X, C);
	}

	
}