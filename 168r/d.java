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
		Pair[][] mat = new Pair[n][m];
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) {
				int val = in.nextInt();
				mat[i][j] = new Pair(val, j);
			}
		int[] limit = new int[m], prt = new int[m], pos = new int[n], next = new int[n];
		int tot = 0;
		for (int i = 0; i < n; ++i)
			Arrays.sort(mat[i]);
		for (int i = 0; i < m; ++i)
			limit[i] = n;
		for (int i = 0; i < n; ++i) {
			int minValue = -1;
			pos[i] = m;
			for (int j = 0; j < m; ++j)
				if (mat[i][j].key != -1) {
					minValue = mat[i][j].key;
					pos[i] = j;
					break;
				}
			for (int j = 0; j < m; ++j)
				if (mat[i][j].key <= minValue) {
					--limit[mat[i][j].index];
					++next[i];
				}
		}
		Queue<Integer> q = new LinkedList<Integer>();
		for (int i = 0; i < m; ++i)
			if (limit[i] == 0) {
				q.offer(i);
			}
		boolean[] able = new boolean[m];
		while (q.size() != 0) {
			int x = q.poll();
			able[x] = true;
			prt[tot++] = x + 1;
			for (int i = 0; i < n; ++i) {
				while (pos[i] < m && able[mat[i][pos[i]].index]) ++pos[i];
				while (next[i] < m && mat[i][next[i]].key == mat[i][pos[i]].key) {
					int col = next[i];
					--limit[mat[i][col].index];
					if (limit[mat[i][col].index] == 0) {
						q.offer(mat[i][col].index);
					}
					++next[i];
				}
			}
		}

		if (tot < m) {
			out.println(-1);
		}
		else {
			for (int i = 0; i < m; ++i)
				if (i == m - 1)
					out.println(prt[i]);
				else
					out.print(prt[i] + " ");
		}

		out.close();
	}
}

class Pair implements Comparable<Pair> {
	int key, index;
	Pair(int key, int index) {
		this.key = key;
		this.index = index;
	}
	public int compareTo(Pair o) {
		if (key != o.key)
			return key < o.key ? -1 : 1;
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

