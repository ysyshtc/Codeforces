import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
	final static int MD = 1000000007;
	static int[] disjoint;

	static int findRoot(int u) {
		if (disjoint[u] == u)
			return u;
		else {
			disjoint[u] = findRoot(disjoint[u]);
			return disjoint[u];
		}
	}
	static int merge(int u, int v) {
		u = findRoot(u);
		v = findRoot(v);
		if (u != v)
			disjoint[u] = v;
		return v;
	}
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		PrintWriter out = new PrintWriter(System.out);

		int n = in.nextInt(), m = in.nextInt(), k = in.nextInt();
		disjoint = new int[n];
		for (int i = 0; i < n; ++i)
			disjoint[i] = i;

		for (int i = 0; i <= n - k; ++i)
			for (int j = 0; j < k; ++j)
				merge(i + j, i + k - 1 - j);

		long ret = 1;
		for (int i = 0; i < n; ++i)
			if (disjoint[i] == i)
				ret = ret * m % MD;
		out.println(ret);
		out.close();
	}
}
