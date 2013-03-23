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
		int[] pos = new int[n + n];
		for (int i = 0; i < n; ++i)
			pos[i] = i + 1;
		int count = 0;
		for (int i = 2; i <= n; ++i) {
			int rem = n % i;
			if (rem > 0)
				pos[n + i - 2] = pos[n / i * i + i - 2];
			for (int j = n / i * i + i - 2; j > i - 2; j -= i)
				pos[j] = pos[j - i];
		}

		for (int i = n - 1; i < n + n - 1; ++i)
			out.print(pos[i] + " ");
		out.println();

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

