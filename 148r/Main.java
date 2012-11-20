import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}

	final static int INF = 11111;
	int[][][] dp;
	boolean[] visited;
	Edge[] firstEdge;

	void dfs(int x) {
		visited[x] = true;
		ArrayList<Integer> index = new ArrayList<Integer>();
		ArrayList<Boolean> dir = new ArrayList<Boolean>();
		for (Edge curEdge = firstEdge[x]; curEdge != null; curEdge = curEdge.next) {
			int to = curEdge.to;
			if (!visited[to]) {
				index.add(to);
				dir.add(curEdge.op);
				dfs(to);
			}
		}

		int m = index.size();
		int[][] g = new int[m + 1][3];
		for (int i = 1; i <= m; ++i)
			Arrays.fill(g[i], INF);
		for (int i = 0; i < m; ++i) {
			int to = index.get(i);
			boolean op = dir.get(i);
			for (int j = 0; j < 3; ++j) {
				for (int k = 0; j + k < 3; ++k) {
					int cost = op ? 0 : 1;
					g[i + 1][j + k] = Math.min(g[i + 1][j + k], g[i][j] + dp[to][k][1]);
					g[i + 1][j + k] = Math.min(g[i + 1][j + k], g[i][j] + dp[to][k][0] + cost);
				}
			}
		}
		int[][][] f = new int[m + 1][3][2];
		for (int i = 1; i <= m; ++i)
			for (int j = 0; j < 3; ++j)
				Arrays.fill(f[i][j], INF);
		f[0][0][1] = f[0][1][1] = f[0][2][1] = INF;
		for (int i = 0; i < m; ++i) {
			int to = index.get(i);
			boolean op = dir.get(i);
			for (int j = 0; j < 3; ++j) 
				for (int k = 0; k < 2; ++k) {
					for (int l = 0; j + l < 3; ++l) {
						int cost = op ? 0 : 1;
						f[i + 1][j + l][k] = Math.min(f[i + 1][j + l][k], f[i][j][k] + dp[to][l][1]);
						f[i + 1][j + l][k] = Math.min(f[i + 1][j + l][k], f[i][j][k] + dp[to][l][0] + cost);

						cost = 1 - cost;
						f[i + 1][j + l][1] = Math.min(f[i + 1][j + l][1], f[i][j][k] + dp[to][l][1] + cost);
					}
			}
		}
		for (int i = 0; i < 3; ++i) {
			dp[x][i][0] = g[m][i];
			dp[x][i][1] = f[m][i][1];
			if (i > 0)
				dp[x][i][1] = Math.min(dp[x][i][1], g[m][i - 1]);
		}
	}

	void run() {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);
		int n = in.nextInt();

		firstEdge = new Edge[n + 1];
		for (int i = 1; i < n; ++i) {
			int u = in.nextInt(), v = in.nextInt();
			firstEdge[u] = new Edge(firstEdge[u], v, true);
			firstEdge[v] = new Edge(firstEdge[v], u, false);
		}
		dp = new int[n + 1][3][2];
		visited = new boolean[n + 1];
		dfs(1);
		out.println(dp[1][2][1]);
		out.close();
	}
}

class Edge {
	Edge next;
	int to;
	boolean op;
	Edge(Edge next, int to, boolean op) {
		this.next = next;
		this.to = to;
		this.op = op;
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

