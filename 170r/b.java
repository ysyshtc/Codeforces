import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}
	final static int STEP = 10000;
	void run() {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);

		int n = in.nextInt(), m = in.nextInt();
		if (n == 6 && m == 3 || n == 5 && m == 3) {
			out.println(-1);
		}
		else {
			int val = 0, del = STEP;
			for (int i = 0; i < m; ++i) {
				val += del;
				del += STEP;
				out.print(n + n - i);
				out.print(" ");
				out.println(val);
			}
			val = 0; del = STEP;
			for (int i = 0; i < n - m; ++i) {
				val -= del;
				del += STEP;
				out.print(-n - n + i);
				out.print(" ");
				out.println(val);
			}
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

