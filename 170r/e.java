import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}
	final static double EPS = 1e-6;
	final static double INF = 1e7;
	int n;
	int[] match;
	boolean[] vx, vy;
	double[] lx, ly;
	double[][] mat;

	boolean find(int x) {
		vx[x] = true;
		for (int i = 1; i <= n + n; ++i)
			if (!vy[i] && Math.abs(lx[x] + ly[i] - mat[x][i]) < EPS) {
				vy[i] = true;
				int tmp = match[i];
				match[i] = x;
				if (tmp == 0 || find(tmp))
					return true;
				match[i] = tmp;
			}
		return false;
	}
	double dist(double x1, double y1, double x2, double y2) {
		return Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	}

	void run() {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);

		n = in.nextInt();
		int[] x = new int[n + 1], y = new int[n + 1];
		int maxy = -1001, tot = 0;
		for (int i = 1; i <= n; ++i) {
			x[i] = in.nextInt();
			y[i] = in.nextInt();
			maxy = Math.max(y[i], maxy);
		}
		for (int i = 1; i <= n; ++i)
			if (maxy == y[i])
				++tot;
		if (tot > 1) {
			out.println(-1);
			out.close();
			return;
		}
		mat = new double[n + n + 1][n + n + 1];
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (y[i] == maxy) {
					mat[i][j] = 0;
					mat[i][j + n] = 0;
				}
				else if (y[i] < y[j]) {
					mat[i][j] = dist(x[i], y[i], x[j], y[j]);
					mat[i][j + n] = dist(x[i], y[i], x[j], y[j]);
				}
				else {
					mat[i][j] = INF;
					mat[i][j + n] = INF;
				}
		for (int i = 1; i <= n + n; ++i)
			for (int j = 1; j <= n + n; ++j)
				mat[i][j] = INF - mat[i][j];
		match = new int[n + n + 1];
		vx = new boolean[n + n + 1];
		vy = new boolean[n + n + 1];
		lx = new double[n + n + 1];
		ly = new double[n + n + 1];
		for (int i = 1; i <= n + n; ++i)
			for (int j = 1; j <= n + n; ++j)
				lx[i] = Math.max(lx[i], mat[i][j]);

		for (int i = 1; i <= n + n; ++i) {
			while (true) {
				Arrays.fill(vx, false);
				Arrays.fill(vy, false);
				if (find(i))
					break;
				double del = INF;
				for (int j = 1; j <= n + n; ++j)
					if (vx[j])
						for (int k = 1; k <= n + n; ++k)
							if (!vy[k])
								del = Math.min(del, lx[j] + ly[k] - mat[j][k]);
				for (int j = 1; j <= n + n; ++j) {
					if (vx[j])
						lx[j] -= del;
					if (vy[j])
						ly[j] += del;
				}
			}
		}

		double ret = 0;
		for (int i = 1; i <= n + n; ++i) {
			ret += lx[i] + ly[i];
		}

		if (2 * n * INF - ret > INF / 2)
			out.println(-1);
		else
			out.println(2 * n * INF - ret);

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

