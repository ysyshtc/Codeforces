import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}
	final static int MAXN = 2222;
	final static int MOD = 1 << 30;
	int gcd(int a, int b) {
		return b == 0 ? a : gcd(b, a % b);
	}
	int calc(int d, int n) {
		int ret = 0;
		for (int i = 1; i <= n; ++i)
			if (gcd(d, i) == 1)
				ret += n / i;
		return ret;
	}
	void run() {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);

		int a = in.nextInt(), b = in.nextInt(), c = in.nextInt();
		int[] u = new int[MAXN];
		u[1] = 1;
		for (int i = 1; i < MAXN; ++i)
			for (int j = i + i; j < MAXN; j += i)
				u[j] -= u[i];
		int ans = 0;
		for (int i = 1; i <= a; ++i) {
			for (int j = 1; j <= b && j <= c; ++j)
				if (gcd(i, j) == 1) {
					ans += a / i * u[j] * calc(i, b / j) * calc(i, c / j);
				}
		}

		out.println(ans & (MOD - 1));
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

