import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}
	void run() {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);

		int n = in.nextInt(), m = in.nextInt();
		int[] a = new int[n];
		for (int i = 0; i < n; ++i) {
			a[i] = in.nextInt();
			double tmp = in.nextDouble();
		}
		int[][] dp = new int[n + 1][m + 1];
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= m; ++j)
				dp[i][j] = n + 1;
		for (int i = 0; i <= n; ++i)
			dp[i][0] = i;
		for (int i = 0; i < n; ++i) {
			int val = a[i];
			for (int j = 0; j <= m; ++j) {
				dp[i + 1][j] = Math.min(dp[i + 1][j], dp[i][j] + 1);
				if (j <= val)
					dp[i + 1][val] = Math.min(dp[i + 1][val], dp[i][j]);
			}
		}
		int ret = n + 1;
		for (int i = 0; i <= m; ++i)
			ret = Math.min(ret, dp[n][i]);
		out.println(ret);

		out.close();
	}
}

class InputReader {
	BufferedReader buff;
	StringTokenizer tokenizer;

	InputReader(InputStream stream) {
		buff = new BufferedReader(new InputStreamReader(stream));
		tokenizer = null;
	}
	boolean hasNext() {
		while (tokenizer == null || !tokenizer.hasMoreTokens())
			try {
				tokenizer = new StringTokenizer(buff.readLine());
			}
			catch (Exception e) {
				return false;
			}
		return true;
	}
	String next() {
		if (!hasNext())
			throw new RuntimeException();
		return tokenizer.nextToken();
	}
	int nextInt() { return Integer.parseInt(next()); }
	long nextLong() { return Long.parseLong(next()); }
	double nextDouble() { return Double.parseDouble(next()); }
}

