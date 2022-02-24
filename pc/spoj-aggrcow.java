import java.util.*;
import java.lang.*;

/*
complexity O(clogc*logs)
c=number of cows
s=number of stalls
*/
class aggrcow {

	static int sumArray(int[] a, int size) {
		int sum = 0;
		for(int i=0;i<size;i++) {
			sum= sum+a[i];
		}
		return sum;
	}

	static int f(int x) { //negative goes to positive
		if (x<0) return -x;
		return x;
	}

	/*
	i use the partition function to calculate if its possible to
	divide the cows with m space, returns true if yes, false otherwise
	*/
	static boolean partition(int[] a, int m, int cows, int n) {
		int count=1;
		int tmp;
		int i=a[0];
		while(i<a[n-1] && count!=cows) {
			tmp=Arrays.binarySearch(a,0,n,i+m);
			if (tmp<0) tmp = f(tmp)-1;
			if (f(tmp)==n) return false;
			//System.out.println("searching... "+ i+ "+" + m);
			//System.out.println("got... "+a[tmp]);
			//if (tmp<0) tmp++;
			i=a[f(tmp)];
			count++;
		}
		if (count==cows) return true;
		return false;
	}


	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		int c, n, t,tmp, middle, high, low;
		int[] stalls;
		middle = 0; //dummy

		t = sc.nextInt();
		for (int i=0;i<t;i++) {
			n = sc.nextInt();
			c = sc.nextInt();
			stalls = new int[n];
			for (int j=0;j<n;j++) {
				stalls[j] = sc.nextInt();
			}
			Arrays.sort(stalls);
			high = sumArray(stalls,n); //the high should not be this, but works fine
			low = 1;
			while(low!=high) {
			/*	i use binary search with the max number of partitions and 1 to
				find the largest minimum distance */
				middle=1+(high+low)/2;
				//System.out.println("low= " + low + " high= " + high + " middle= " + middle);
				if (partition(stalls,middle, c,n)) low = middle;
				else high = middle-1;
			}
			System.out.println(low);
		}
	}
}