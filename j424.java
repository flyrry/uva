import java.math.BigInteger;
import java.io.*;

public class j424 {
  public static void main(String args[]) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    String line;
    BigInteger sum = new BigInteger("0");
    while (!(line = in.readLine().trim()).equals("0")) {
      BigInteger n = new BigInteger(line);
      sum = sum.add(n);
    }
    System.out.println(sum.toString());
  }
}
