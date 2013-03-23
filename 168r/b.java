import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}
	Edge[] firstEdge;
	int[] val;
	long[] add, sub;
	void dfs(int x, int father) {
		long u = 0, v = 0;
		for (Edge curEdge = firstEdge[x]; curEdge != null; curEdge = curEdge.next) {
			int to = curEdge.to;
			if (to != father) {
				dfs(to, x);
				u = Math.max(u, add[to]);
				v = Math.max(v, sub[to]);
			}
		}
		if (val[x] + u - v > 0)
			v += val[x] + u - v;
		else
			u -= val[x] + u - v;
		add[x] = u;
		sub[x] = v;
	}

	void run() {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);

		int n = in.nextInt();
		firstEdge = new Edge[n + 1];
		val = new int[n + 1];
		add = new long[n + 1];
		sub = new long[n + 1];
		for (int i = 1; i < n; ++i) {
			int u = in.nextInt(), v = in.nextInt();
			firstEdge[u] = new Edge(v, firstEdge[u]);
			firstEdge[v] = new Edge(u, firstEdge[v]);
		}
		for (int i = 1; i <= n; ++i)
			val[i] = in.nextInt();
		dfs(1, -1);
		out.println(add[1] + sub[1]);
		out.close();
	}
}

class Edge {
	int to;
	Edge next;
	Edge(int to, Edge next) {
		this.to = to;
		this.next = next;
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

