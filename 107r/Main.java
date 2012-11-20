import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);

		Task solver = new Task();
		solver.solve();

		out.close();
	}
}

class InputReader {
	BufferedReader buff;
	StringTokenizer tokenizer;

	InputReader(InputStream stream) {
		buff = new BufferedReader(new InputStreamReader(stream));
		tokenizer = null
	}
	String next() {
		while (tokenizer == null || !tokenizer.hasMoreTokens())
			try {
				tokenizer = new StringTokenizer(buff.readLine());
			}
			catch (IOException e) {
				throw RuntimueException(e);
			}
		return tokenizer.nextToken();
	}
	int nextInt() { return Integer.parseInt(next()); }
}

class Task {
	void solve(InputReader in, PrintWriter out) {
		int n = in.nextInt(), l = in.nextInt(), r = in.nextInt();
		for (int i = 1; i < n; ++i) {
			int u = in.nextInt(), v = in.nextInt(), c = in.nextInt();
		}
	}
}
