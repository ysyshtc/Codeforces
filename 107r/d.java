import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		PrintWriter out = new PrintWriter(System.out);

		Task solver = new Task();
		solver.solve(in, out);
		out.close();
	}
}

class Task {
	final static int INF = 0x3fffffff;

	void solve(Scanner in, PrintWriter out) {
		int n = in.nextInt();
		int[] val = new int[n + 1];
		for (int i = 1; i <= n; ++i)
			val[i] = in.nextInt();
		String s = in.next();
		int[] a = new int[n];
		for (int i = 0; i < n; ++i)
			a[i] = s.charAt(i);

		int[][][] dp = new int[n][n][n + 1];
		int[][] best = new int[n][n];
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				Arrays.fill(dp[i][j], -INF);

		for (int i = 0; i < n; ++i) {
			dp[i][i][1] = 0;
			if (val[1] != -1)
				dp[i][i][0] = val[1];
		}

		for (int j = 1; j < n; ++j)
			for (int i = j - 1; i >= 0; --i)
				for (int k = 1; k <= j - i + 1; ++k) {
					for (int l = i; l < j; ++l)
						dp[i][j][k] = Math.max(dp[i][j][k], dp[i][l][0] + dp[l + 1][j][k]);
					for (int l = i + 1; l <= j; ++l)
						dp[i][j][k] = Math.max(dp[i][j][k], dp[l][j][0] + dp[i][l - 1][k]);
					if (a[i] == a[j] && k >= 2)
						if (i == j - 1)
							dp[i][j][k] = Math.max(dp[i][j][k], 0);
						else
							dp[i][j][k] = Math.max(dp[i][j][k], dp[i + 1][j - 1][k - 2]);
					if (val[k] != -1)
						dp[i][j][0] = Math.max(dp[i][j][0], dp[i][j][k] + val[k]);
				}

		int[] ret = new int[n + 1];
		for (int i = 1; i <= n; ++i) {
			ret[i] = ret[i - 1];
			for (int j = 1; j <= i; ++j)
				ret[i] = Math.max(ret[i], ret[j - 1] + dp[j - 1][i - 1][0]);
		}
		out.println(ret[n]);
	}
}
