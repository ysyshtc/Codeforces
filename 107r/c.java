import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
	public static void main(String[] args) {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);

		Task solver = new Task();
		solver.solve(in, out);
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

	String next() {
		while (tokenizer == null || !tokenizer.hasMoreTokens())
			try {
				tokenizer = new StringTokenizer(buff.readLine());
			}
			catch (IOException e) {
				throw new RuntimeException(e);
			}
		return tokenizer.nextToken();
	}

	int nextInt() { return Integer.parseInt(next()); }
	long nextLong() { return Long.parseLong(next()); }
}

class Node {
	long value, maxValue, leftValue, rightValue;
	Node(long c) {
		this.value = c;
		this.maxValue = Math.max(c, 0);
		this.leftValue = Math.max(c, 0);
		this.rightValue = Math.max(c, 0);
	}
	Node(long c, long p, long u, long v) {
		this.value = c;
		this.maxValue = p;
		this.leftValue = u;
		this.rightValue = v;
	}

	Node merge(Node o) {
		long c = value + o.value;
		long p = Math.max(Math.max(maxValue, o.maxValue), rightValue + o.leftValue);
		long u = Math.max(value + o.leftValue, leftValue);
		long v = Math.max(rightValue + o.value, o.rightValue);
		return new Node(c, p, u, v);
	}
}

class SegmentTree {
	SegmentTree lch, rch;
	int left, right;
	Node data;

	SegmentTree(SegmentTree lch, SegmentTree rch, int left, int right, Node c) {
		this.lch = lch; this.rch = rch;
		this.left = left; this.right = right;
		this.data = c;
	}

	static SegmentTree build(int l, int r, long[] val) {
		if (l == r - 1)
			return new SegmentTree(null, null, l, r, new Node(val[l]));

		int mid = (l + r + 1) / 2;
		SegmentTree p = build(l, mid, val);
		SegmentTree q = build(mid, r, val);
		return new SegmentTree(p, q, l, r, p.data.merge(q.data));
	}

	Node get(int u, int v) {
		if (u <= left && right <= v)
			return data;
		int mid = (left + right + 1) / 2;
		Node ret = new Node(0);
		if (left < v && u < mid)
			ret = ret.merge(lch.get(u, v));
		if (mid < v && u < right)
			ret = ret.merge(rch.get(u, v));
		return ret;
	}
}

class Task {
	void solve(InputReader in, PrintWriter out) {
		int n = in.nextInt(), m = in.nextInt(), c = in.nextInt();
		long[] x = new long[n], val = new long[n];

		for (int i = 0; i < n; ++i)
			x[i] = in.nextLong();
		for (int i = 1; i < n; ++i) {
			int prob = in.nextInt();
			val[i] = 50 * (x[i] - x[i - 1]) - c * prob;
		}
		
		SegmentTree root = SegmentTree.build(1, n, val);
		long ret = 0;
		for (int i = 0; i < m; ++i) {
			int u = in.nextInt(), v = in.nextInt();
			ret += root.get(u, v).maxValue;
		}
		out.println(ret / 100.0);
	}
}
