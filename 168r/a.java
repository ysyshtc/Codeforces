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

		int n = in.nextInt(), k = in.nextInt();
		int[] a = new int[n];
		for (int i = 0; i < n; ++i)
			a[i] = in.nextInt();
		Arrays.sort(a);
		int ret = 0, it = 0;
		for (int i = 0; i < n; ++i) {
			int val = a[i] % k == 0 ? a[i] / k : -1;
			while (it < i && a[it] < val) ++it;
			if (it == i || a[it] != val) {
				++ret;
			}
			else {
				a[i] = 0;
			}
		}
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

