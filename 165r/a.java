import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}
	int contain(int x, int d) {
		if (d > 14)
			return 1;
		int ret = x >> d >> d;
		if (ret << d << d < x)
			++ret;
		return ret;
	}

	void run() {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);

		int n = in.nextInt();
		Box[] a = new Box[n];
		for (int i = 0; i < n; ++i) {
			int u = in.nextInt(), v = in.nextInt();
			a[i] = new Box(u, v);
		}
		Arrays.sort(a);
		for (int i = 0; i < n - 1; ++i) {
			int diff = a[i + 1].size - a[i].size;
			a[i + 1].num = Math.max(contain(a[i].num, diff), a[i + 1].num);
		}
		int ret = a[n - 1].size + 1;
		while (contain(a[n - 1].num, ret - a[n - 1].size) > 1) ++ret;

		out.println(ret);
		out.close();
	}
}

class Box implements Comparable<Box> {
	int size, num;
	Box(int size, int num) {
		this.size = size;
		this.num = num;
	}
	public int compareTo(Box o) {
		if (size != o.size)
			return size < o.size ? -1 : 1;
		return 0;
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

