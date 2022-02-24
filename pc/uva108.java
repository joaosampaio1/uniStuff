import java.util.*;
import java.lang.*;

/*
complexity O(n²log²n)
n=size of a row 
0 1 2
3 4 5 n=3
6 7 8
*/
class uva108 {

	static int getMax(int[][] m, int n){ //search for the max value in matrix
		int sum = 0;
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) {
				if (m[i][j]>sum) sum = m[i][j];
			}
		}
		return sum;
	}

	static void printArray(int[][] m, int n){ //debug
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) {
				System.out.print("m["+i+"]["+j+"]="+m[i][j]+ " ");
			}
			System.out.println();
		}
	}

	public static void main(String[] args) {
		int n, tmp;
		int[][] m, cs, sums;
		Scanner sc = new Scanner(System.in);

		n = sc.nextInt();
		m = new int[n+1][n+1];
		sums = new int[n+1][n+1];
		cs = new int[n+1][n+1];

		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) {
				m[i][j] = sc.nextInt();
			}
		}

		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) {
				cs[i][j] = m[i][j] + cs[i-1][j] + cs[i][j-1] - cs[i-1][j-1]; //make the cumulative sums
			}
		}
		for (int d=1;d<=n;d++) {
			for (int c=1;c<=n;c++) {
				for (int b=1;b<=d;b++) {
					for (int a=1;a<=c;a++) {
						tmp = cs[c][d] - cs[a-1][d] - cs[c][b-1] + cs[a-1][b-1]; //make the best possible cumulative sqaures in sums matrix
						//System.out.println("tmp = " + tmp);
						if (tmp > sums[a][b]) sums[a][b] = tmp;
					}
				}
			}
		}

		//printArray(sums,n);
		System.out.println(getMax(sums, n));	
	}
}