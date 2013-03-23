import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}
	final static long INF = 0x3fffffffL << 30;

	long choose(Node[] heap, int index) {
		for (int i = 0; i < 2; ++i)
			if (index != heap[i].index)
				return heap[i].val;
		return -INF;
	}

	void update(Node[] heap, long val, int index) {
		for (int i = 0; i < 2; ++i)
			if (index == heap[i].index) {
				heap[i].val = val;
				if (i == 1 && val > heap[0].val) {
					Node swap = heap[0];
					heap[0] = heap[1];
					heap[1] = swap;
				}
				return;
			}
		for (int i = 0; i < 2; ++i)
			if (heap[i].val < val) {
				for (int j = 1; j > i; --j)
					heap[j] = heap[j - 1];
				heap[i] = new Node(val, index);
				return;
			}
	}

	void run() {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);

		int n = in.nextInt(), q = in.nextInt();
		int[] v = new int[n], c = new int[n];
		for (int i = 0; i < n; ++i)
			v[i] = in.nextInt();
		for (int i = 0; i < n; ++i)
			c[i] = in.nextInt();

		for (int i = 0; i < q; ++i) {
			int a = in.nextInt(), b = in.nextInt();
			long[] dp = new long[n + 1];
			Node[] heap = new Node[2];
			Arrays.fill(dp, -INF);
			for (int j = 0; j < 2; ++j)
				heap[j] = new Node(-INF, -1);
			for (int j = 0; j < n; ++j) {
				long val = v[j], maxv = val * b;
				int color = c[j];
				maxv = Math.max(dp[color] + val * a, maxv);
				maxv = Math.max(choose(heap, color) + val * b, maxv);
				dp[color] = Math.max(maxv, dp[color]);
				update(heap, dp[color], color);
			}

			long ret = 0;
			for (int j = 1; j <= n; ++j)
				ret = Math.max(ret, dp[j]);
			out.println(ret);
		}

		out.close();
	}
}

class Node implements Comparable<Node> {
	long val;
	int index;
	Node(long val, int index) {
		this.val = val; this.index = index;
	}

	public int compareTo(Node o) {
		if (val != o.val)
			return val > o.val ? -1 : 1;
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

