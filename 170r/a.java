import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}
	int[] root;
	int findRoot(int x) {
		if (root[x] == 0)
			return x;
		int ret = findRoot(root[x]);
		root[x] = ret;
		return ret;
	}
	boolean merge(int u, int v) {
		int p = findRoot(u), q = findRoot(v);
		if (p != q) {
			root[p] = q;
			return true;
		}
		return false;
	}
	void run() {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);

		int n = in.nextInt(), m = in.nextInt(), tot = 0;
		root = new int[n + m + 1];
		for (int i = 1; i <= n; ++i) {
			int k = in.nextInt();
			tot += k;
			for (int j = 0; j < k; ++j) {
				int x = in.nextInt();
				merge(x + n, i);
			}
		}
		int ret = 0;
		for (int i = 1; i <= n; ++i)
			if (root[i] == 0)
				++ret;
		if (ret > 0 && tot > 0)
			--ret;

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

