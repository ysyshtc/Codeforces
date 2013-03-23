import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}
	final static int MAXC = 111111;
	void run() {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);

		ArrayList[] factor = new ArrayList[MAXC];
		for (int i = 0; i < MAXC; ++i)
			factor[i] = new ArrayList<Integer>();
		boolean[] prim = new boolean[MAXC];
		for (int i = 2; i < MAXC; ++i)
			if (!prim[i]) {
				factor[i].add(i);
				for (int j = i + i; j < MAXC; j += i) {
					prim[j] = true;
					factor[j].add(i);
				}
			}

		int n = in.nextInt();
		int[] a = new int[n], dp = new int[MAXC];
		for (int i = 0; i < n; ++i)
			a[i] = in.nextInt();

		for (int i = 0; i < n; ++i) {
			int val = a[i], maxv = 1;
			for (int j = 0; j < factor[val].size(); ++j) {
				int p = (Integer)factor[val].get(j);
				maxv = Math.max(maxv, dp[p] + 1);
			}
			for (int j = 0; j < factor[val].size(); ++j) {
				int p = (Integer)factor[val].get(j);
				dp[p] = Math.max(maxv, dp[p]);
			}
		}
		int ret = 1;
		for (int i = 2; i < MAXC; ++i)
			ret = Math.max(ret, dp[i]);

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
}

