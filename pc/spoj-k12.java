import java.util.*;
import java.lang.*;

/*
complexity per case = O(log3h)
h=max height
*/
class k12 {

	static void printMin(long[] f, int n) { 
		long min = Long.MAX_VALUE;
		for (int j=0;j<=n;j++) {
			//System.out.println(f[j]);
			if (f[j]<min && f[j]!=-1) min = f[j];
		}
		//printArray(f,n);
		System.out.println(min);
	}

	static int abs(int x) { //negative goes to positive
		if (x<0) return -x;
		return x;
	}

	static void tSearch(int[] c, int[] h, int maxHeight, int n) { //recursive caller

		//f = 	costs to get every building to height(x)
		//ex.. f[2] cost to get every building height(2)
		long[] f = new long[maxHeight+1]; 
		Arrays.fill(f, -1);
		tSearch(f,c,h,n,maxHeight,0);
		printMin(f, maxHeight);
	}

	static void fill(long[] f,int[] c, int[] h,int n, int key) { //fills the function f
		if(f[key]==-1) {
			f[key]++;
			for (int k=0;k<n;k++) {
				f[key] = f[key] + abs(key-h[k])*c[k];
				//System.out.println(key);
			}
				
		}
	}

	//recursive ternary search
	static void tSearch(long[] f,int[] c, int[] h,int n, int high, int low) { 
		
		if (high-low<=2) {
			for(int i=low;i<=high;i++) {
				fill(f,c,h,n,i);
			}
			return;
		}
		//System.out.println(low + " " + f[low]);
		//System.out.println(high + " " +f[high]);
		int m1 = (high+(2*low))/3;
		int m2 = (2*high+low)/3;
		fill(f,c,h,n,m1);
		fill(f,c,h,n,m2);
		
		if (f[m2] < f[m1]) {
			tSearch(f,c,h,n,high,m1); //<  =min
		}
		else tSearch(f,c,h,n,m2,low);
	}

	static void printArray(int[] f, int n) { //debug print
		for (int j=0;j<=n;j++) {
			System.out.println("f["+j+"]= "+f[j]);
		}
	}	

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		int t, n;
		int[] h; //heights
		int[] c; //costs
		int maxHeight;
		
		t = sc.nextInt();
		for (int i=0;i<t;i++) {
			maxHeight = 0;
			n = sc.nextInt();
			c = new int[n];
			h = new int[n];
			for (int j=0;j<n;j++) {
				h[j] = sc.nextInt();
				if (maxHeight<h[j]) maxHeight = h[j];
			}

			for (int j=0;j<n;j++) {
				c[j] = sc.nextInt();
			}

			tSearch(c,h,maxHeight,n);	
		}
	}
}
