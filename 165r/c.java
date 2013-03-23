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

		int n = in.nextInt(), m = in.nextInt();
		Edge[] firstEdge = new Edge[n + 1];
		int[] ret = new int[m], flow = new int[n + 1];
		Arrays.fill(ret, -1);
		for (int i = 0; i < m; ++i) {
			int u = in.nextInt(), v = in.nextInt(), c = in.nextInt();
			firstEdge[u] = new Edge(v, c, firstEdge[u], i, false);
			firstEdge[v] = new Edge(u, c, firstEdge[v], i, true);
			flow[u] += c;
			flow[v] += c;
		}
		Queue<Integer> q = new LinkedList<Integer>();
		flow[1] = 0;
		for (int i = 2; i < n; ++i) flow[i] /= 2;
		q.offer(1);
		while (q.size() > 0) {
			int v = q.poll();
			for (Edge cur = firstEdge[v]; cur != null; cur = cur.next) {
				int to = cur.to;
				if (ret[cur.index] == -1)
					ret[cur.index] = cur.ori ? 1 : 0;
				flow[to] -= cur.val;
				if (flow[to] == 0)
					q.offer(to);
			}
		}

		for (int i = 0; i < m; ++i)
			out.println(ret[i]);
		out.close();
	}
}

class Edge {
	int to, val, index;
	Edge next;
	boolean ori;
	Edge(int to, int val, Edge next, int index, boolean ori) {
		this.to = to;
		this.val = val;
		this.next = next;
		this.index = index;
		this.ori = ori;
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

