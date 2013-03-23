import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}

	final static int PERIOD = 60;
	final static int POWER = 13;

	long fib(long n, long mod) {
		long[][] mat = new long[2][2];
		mat[0][1] = mat[1][0] = mat[1][1] = 1;
		Matrix v = new Matrix(mat);
		v = v.power(n, mod);
		return v.mat[0][1];
	}

	void run() {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);

		long num = in.nextLong(), mod = 10, per = PERIOD;
		ArrayList<Long> valid = new ArrayList<Long>();
		for (int i = 0; i < PERIOD; ++i)
			if (fib(i, mod) == num % mod)
				valid.add((long)i);

		for (int i = 1; i < POWER; ++i) {
			mod *= 10;
			long rem = num % mod;
			ArrayList<Long> nv = new ArrayList<Long>();
			for (int j = 0; j < 10; ++j)
				for (int k = 0; k < valid.size(); ++k) {
					if (fib(j * per + valid.get(k), mod) == rem)
						nv.add(j * per + valid.get(k));
				}
			valid = nv;
			per *= 10;
		}

		if (valid.size() == 0)
			out.println(-1);
		else
			out.println(valid.get(0));
		out.close();
	}
}

class Matrix {
	long[][] mat;
	final static Matrix ONE = new Matrix(new long[][] {{1, 0}, {0, 1}});
	Matrix(long[][] mat) {
		this.mat = mat;
	}
	long add(long a, long b, long mod) {
		if (a + b >= mod)
			return a + b - mod;
		return a + b;
	}
	long multiply(long a, long b, long mod) {
		long ret = 0;
		while (a > 0) {
			if ((a & 1) == 1)
				ret = add(ret, b, mod);
			b = add(b, b, mod);
			a >>= 1;
		}
		return ret;
	}
	Matrix multiply(Matrix o, long mod) {
		long[][] ret = new long[2][2];
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				for (int k = 0; k < 2; ++k)
					ret[i][j] = add(ret[i][j], multiply(mat[i][k], o.mat[k][j], mod), mod);
		return new Matrix(ret);
	}
	Matrix power(long p, long mod) {
		if (p == 0) {
			return Matrix.ONE;
		}
		Matrix ret = power(p / 2, mod);
		ret = ret.multiply(ret, mod);
		if ((p & 1) == 1)
			ret = ret.multiply(this, mod);
		return ret;
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

