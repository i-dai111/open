import java.net.URL;
import java.net.HttpURLConnection;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.TreeSet;

class Main {
  public static void main(String[] args) {
		int i=1;
		System.out.println("Links in https://www.osakafu-u.ac.jp/");
		Pattern pattern1 = Pattern.compile("href=[\"\']http.?://[0-9a-zA-Z/_.-]{1,2048}/[\'\"]");
		TreeSet<String> URLTree = new TreeSet();
  try{
		URL url=new URL("https://www.osakafu-u.ac.jp/");
		HttpURLConnection http = (HttpURLConnection)url.openConnection();
		http.setRequestMethod("GET");
		http.connect();
		InputStreamReader isr = new InputStreamReader(http.getInputStream(),"UTF-8");
		BufferedReader br = new BufferedReader(isr);
		String line_buffer;
		while(null != (line_buffer = br.readLine())){
			Matcher matcher1 = pattern1.matcher(line_buffer);
      while (matcher1.find()) {
URLTree.add(matcher1.group());
}
			}
		br.close();
		isr.close();
		http.disconnect();
	}catch( Exception e){}
for(String value : URLTree){
String[] s3=value.split("\"");

System.out.println(i+": "+s3[1]);
i++;
}

  }
}