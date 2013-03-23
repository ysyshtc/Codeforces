import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}
	Edge[] firstEdge;
	double ret;
	void addEdge(int u, int v) {
		firstEdge[u] = new Edge(v, firstEdge[u]);
	}
	void dfs(int x, int length, int father) {
		ret += 1.0 / length;
		for (Edge e = firstEdge[x]; e != null; e = e.next) {
			int to = e.to;
			if (to != father) {
				dfs(to, length + 1, x);
			}
		}
	}
	void run() {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);

		int n = in.nextInt();
		firstEdge = new Edge[n + 1];
		for (int i = 1; i < n; ++i) {
			int u = in.nextInt(), v = in.nextInt();
			addEdge(u, v);
			addEdge(v, u);
		}
		ret = 0;
		dfs(1, 1, -1);
		out.println(ret);
		out.close();
	}
}

class Edge {
	Edge next;
	int to;
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

