import java.util.*;
import java.lang.*;

/*
complexity = O(qlogn)
q=number of queries or change command
n=number of integers
*/
class SegTree {
	int n;
	int t[];

	SegTree(int n) {
		this.n=n;
		t = new int[4*n];
		Arrays.fill(t,1); //fill the tree with one since we need multiplication
	}

	void build(int a[], int v, int tl, int tr) {
	    if (tl == tr) {
	        t[v] = a[tl];
	    } else {
	        int tm = (tl + tr) / 2;
	        build(a, v*2, tl, tm);
	        build(a, v*2+1, tm+1, tr);
	        t[v] = t[v*2] * t[v*2+1];
	    }
	}

	int mul(int v, int tl, int tr, int l, int r) {
		//System.out.println(" v= "+ v +" tl= " + tl + " tr= "+ tr + " l= " + l + " r= " + r);
	    if (l > r) 
	        return 1;
	    if (l == tl && r == tr) {
	        return t[v];
	    }
	    int tm = (tl + tr) / 2;
	    return mul(v*2, tl, tm, l, Math.min(r, tm))
	           * mul(v*2+1, tm+1, tr, Math.max(l, tm+1), r);
	}

	void update(int v, int tl, int tr, int pos, int new_val) {
	    if (tl == tr) {
	        t[v] = new_val;
	    } else {
	        int tm = (tl + tr) / 2;
	        if (pos <= tm)
	            update(v*2, tl, tm, pos, new_val);
	        else
	            update(v*2+1, tm+1, tr, pos, new_val);
	        t[v] = t[v*2] * t[v*2+1];
	    }
	}

	void printArray() { //debug
		for (int i=0;i<4*n;i++) {
			//if (t[i]!=null)
				System.out.println("t["+ i+"]= "+t[i]);
		}
	}

}

class uva12532 {

	static int simplify(int v) { 
		//we only need to know if the integer is positive, negative or zero
		if (v>0) return 1;
		if (v<0) return -1;
		return 0;
	}

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		int n, k, v1, v2;
		int result;
		SegTree s;
		int[] a;
		String str;

		while (sc.hasNextInt()) {	

			n = sc.nextInt();
			a = new int[n];
			s = new SegTree(n);
			k = sc.nextInt();

			for (int i=0;i<n;i++) {
				v1 = simplify(sc.nextInt());
				a[i] = v1;
			}
			s.build(a,1,0,n-1);
			//s.printArray();
			for (int i=0;i<k;i++) {
				str = sc.next();
				v1 = sc.nextInt();
				v2 = sc.nextInt();
				//System.out.println(str+ " "+ v1 + " " + v2);
				
				if(str.equals("C")) { //change something in tree
					v2 = simplify(v2);
					s.update(1,0,n-1,v1-1,v2);
				}
				else { //query
					result = s.mul(1,0,n-1,v1-1,v2-1);
					//System.out.println(result);
					//s.printArray();
					if (result == 0) System.out.print("0");
					if (result > 0) System.out.print("+");
					if (result < 0) System.out.print("-");
				}
			}
			System.out.println();
		}
	}
}