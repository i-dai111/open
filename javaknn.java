// ファイル読み込みのためのimport
// ファイル読み込みのためのimport
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;








//hahhah


public class javaknn {
	// double型2次元配列を表示する関数
	public static void show(double[][] A) {
		for (int i = 0; i < A.length; i++) {
			for (int j = 0; j < A[0].length; j++) {
				System.out.print(A[i][j] + ", ");
			}
			System.out.println();
		}
	}

	// String型1次元配列を表示する関数
	public static void show(String[] a) {
		for (int i = 0; i < a.length; i++) {
			System.out.print(a[i] + ", ");
		}
		System.out.println();
	}

	// k近傍法
	// X, yを訓練データとし，入力xに対しk近傍法を実行し，予測結果を返す．
	public static String knn(double[][] X, String[] y, int k, double[] x) {
		// ここを適切に完成させる
double[] r=new double [X.length];
		String[] yk=new String[y.length];
for(int i=0;i<y.length;i++){
	yk[i]=y[i];
}
		for(int i=0;i<X.length;i++){
			r[i]=0;
		}

		for(int i=0;i<X.length;i++){
			for(int j=0;j<X[0].length;j++){
				r[i]+=(X[i][j]-x[j])*(X[i][j]-x[j]);
			}
		}
//ソート
		double tmp;
		String ytmp;
  for (int i=0; i<r.length; ++i) {
    for (int j=i+1; j<r.length; ++j) {
      if (r[i] > r[j]) {
        tmp =  r[i];
        r[i] = r[j];
        r[j] = tmp;
				ytmp=yk[i];
				yk[i]=yk[j];
				yk[j]=ytmp;
      }
    }
  }


		
int []count =new int[3];
		for(int i=0;i<3;i++){
			count[i]=0;
		}
		
		for(int i=0;i<k;i++){
			if(yk[i].equals("Iris-setosa")){
				count[0]++;
			}else if(yk[i].equals("Iris-versicolor")){
				count[1]++;
			}else if(yk[i].equals("Iris-virginica")){
				count[2]++;
			}
		}
		int mi=1;
		int countmax=0;
for(int i=0;i<3;i++){
	if(count[i]>countmax){
		countmax=count[i];
		mi=i;
	}
}
String set="Iris-setosa";
String ver="Iris-versicolor";
String vir="Iris-virginica";

			if(mi==0){
			System.out.print(set);
			}else if(mi==1){
			System.out.print(ver);
			}else if(mi==2){
			System.out.print(vir);
			}
			System.out.print(":[");
for(int i=0;i<k;i++){
	System.out.printf(yk[i]+",");
}
	System.out.println("]");
		
			if(mi==0){
				return set;
			}else if(mi==1){
				return ver;
			}else{
				return vir;
			}
		
	}

	public static void main(String[] args) {
		// 変数設定
		int n = 150; // 対象数 n
		int m = 4; // 次元数 m
		double[][] X = new double[n][m]; // データ行列 X の宣言
		String[] y = new String[n]; // 教師ラベルの配列

		// データの読込
		try {
			File file = new File("iris.data"); // ファイルのパスを指定する

			// BufferedReaderクラスのreadLineメソッドを使って1行ずつ読み込み表示する
			FileReader fileReader = new FileReader(file);
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			String row;

	
			// ここで X と y にデータを格納する (ここを適切に完成させる)
			// 何らかの処理

			double [] idata=new double [X[0].length];
			int i=0;
			while ((row = bufferedReader.readLine()) != null) {
				// 何らかの処理
		 if ("".equals(row)) {

    }else{	
				
				String data= row.substring(0, 15);
			  y[i]=row.substring(16);
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
		} catch (IOException e) {
			e.printStackTrace();
		}

		// データ行列 X と正解ラベル y の表示
		show(X);
		show(y);

		// パラメータ k を定める．
		int k = 5;
		// 以下でleave-one-out交差検証法でk近傍法の性能を確認する．(ここを適切に完成させる)
	double pre=0;//答えがあった回数
	double[][] Xtemp=new double[X.length-1][X[0].length];
	
		for(int i=0;i<X.length;i++){
			
			for(int j=0;j<X.length-1;j++){//XtempにXを代入
				if(j!=i){
				for(int a=0;a<X[0].length;a++){
					if(j<i){
					Xtemp[j][a]=X[j][a];
				}else{
						Xtemp[j][a]=X[j-1][a];			
			}}}}
				
	
if(knn(Xtemp,y,k,X[i]).equals(y[i])){
	pre++;
};
	
}
System.out.println("Prediction Accuracy="+pre/150);

}
}