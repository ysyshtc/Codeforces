import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}
	int code(char c) {
		return c == 'R' ? 0 : c == 'B' ? 1 : 2;
	}
	void run() {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);

		String s = in.next(), t = in.next();
		int n = s.length(), m = t.length();

		long ret = (long)n * m;
		int[][] c1 = new int[3][3], c2 = new int[3][3];
		for (int i = 1; i < n; ++i) {
			++c1[code(s.charAt(i - 1))][code(s.charAt(i))];
		}
		for (int i = 1; i < m; ++i) {
			++c2[code(t.charAt(i - 1))][code(t.charAt(i))];
		}
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				if (i != j)
					ret -= (long)c1[i][j] * c2[j][i];

		int p = 0;
		for (int i = 0; i < n; ++i) {
			int v = code(s.charAt(i)), u = i == 0 ? -1 : code(s.charAt(i - 1));
			while (p < m && code(t.charAt(p)) != v) {
				if (++p < m)
					--c2[code(t.charAt(p - 1))][code(t.charAt(p))];
			}
			if (p == m)
				break;
			ret -= m - p - 1;
			if (i > 0 && v != u)
				ret += c2[v][u];
			if (p < m - 1)
				--c2[code(t.charAt(p))][code(t.charAt(++p))];
		}

		p = 0;
		for (int i = 0; i < m; ++i) {
			int v = code(t.charAt(i)), u = i == 0 ? -1 : code(t.charAt(i - 1));
			while (p < n && code(s.charAt(p)) != v) {
				if (++p < n)
					--c1[code(s.charAt(p - 1))][code(s.charAt(p))];
			}
			if (p == n)
				break;
			ret -= n - p - 1;
			if (i > 0 && v != u)
				ret += c1[v][u];
			if (p < n - 1)
				--c1[code(s.charAt(p))][code(s.charAt(++p))];
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

