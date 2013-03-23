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

		int n = in.nextInt();
		int[] a = new int[n];
		for (int i = 0; i < n; ++i)
			a[i] = in.nextInt();
		int m = in.nextInt();
		for (int i = 0; i < m; ++i) {
			int v = in.nextInt();
			a[v - 1] = -a[v - 1];
		}

		int[] stack = new int[n];
		int top = 0;
		for (int i = n - 1; i >= 0; --i) {
			if (a[i] < 0) {
				stack[top++] = -a[i];
			}
			else {
				if (top == 0 || stack[top - 1] != a[i]) {
					stack[top++] = a[i];
					a[i] = -a[i];
				}
				else {
					--top;
				}
			}
		}

		if (top > 0) {
			out.println("NO");
		}
		else {
			out.println("YES");
			for (int i = 0; i < n; ++i)
				out.print(a[i] + " ");
			out.println();
		}
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

