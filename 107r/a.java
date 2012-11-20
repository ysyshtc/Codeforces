import java.math.*;
import java.io.*;
import java.util.*;

public class Main {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		PrintWriter out = new PrintWriter(System.out);

		long p = in.nextLong();

		ArrayList<Long> divisor = new ArrayList<Long>();
		for (long i = 2; p / i >= i; ++i)
			if (p % i == 0) {
				divisor.add(i);
				if (p / i != i)
					divisor.add(p / i);
			}
		divisor.add(p);

		Collections.sort(divisor);
		int n = divisor.size();
		long[] dp = new long[n];

		for (int i = 0; i < n; ++i) {
			dp[i] = 0;
			long cur = divisor.get(i);
			for (int j = 0; j < i; ++j)
				if (cur % divisor.get(j) == 0) {
					dp[i] = -1;
					if (dp[j] == -1) {
						dp[i] = divisor.get(j);
						break;
					}
				}
		}
		if (dp[n - 1] == -1)
			out.println(2);
		else {
			out.println(1);
			out.println(dp[n - 1]);
		}
		out.close();
	}
}
