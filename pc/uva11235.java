import java.util.*;
import java.lang.*;

/*
complexity per case = O(qlogn)
q=number of queries
n=number of integers
*/


class Node{
	int rvalue; //most right value
	int lvalue; //most left value
	int rqvalue; //quantity right
	int lqvalue; //quantity left
	int max; //max until

	/*
	    (A)
	    / \
	  (B) (C)

	  A----------
	  rvalue = rvalue(c)
	  lvalue = lvalue(b)
	  rqvalue = rqvalue(c)+if (rqvalue(c)=rqvalue(b)) rqvalue(b)
	  lqvalue = rqvalue(b)+if (rqvalue(b)=rqvalue(c)) rqvalue(c)
	  max = max(rqvalue,lqvalue,max)
	  ------------
	*/

	Node(int value) {
		rvalue = value;
		lvalue = value;
		rqvalue = 1;
		lqvalue = 1;
		max=1 ;
	}

	Node(int lvalue, int rvalue,int lqvalue, int rqvalue, int max) {
		this.rvalue = rvalue;
		this.lvalue = lvalue;
		this.rqvalue = rqvalue;
		this.lqvalue = lqvalue;
		this.max = max;
	}

	int getRValue() {return rvalue;}
	int getLValue() {return lvalue;}
	int getRQValue() {return rqvalue;}
	int getLQValue() {return lqvalue;}
	int getMax() {return max;}
	void setRValue(int rvalue) {this.rvalue=rvalue;}
	void setLValue(int lvalue) {this.lvalue=lvalue;}
	void setRQValue(int rqvalue) {this.rqvalue=rqvalue;}
	void setLQValue(int lqvalue) {this.lqvalue=lqvalue;}
	void setMax(int max) {this.max=max;}
}

class SegTree {

	int n;
	//int t[];
	Node t[];

	SegTree(int n) {
		this.n = n;
		t = new Node[4*n];
	}

	//construct the Segment Tree from a given array a[]
	//v = index
	void build(int a[], int v, int tl, int tr) {
	    if (tl == tr) {
	        t[v] = new Node(a[tl]);
	    } else {
	        int tm = (tl + tr) / 2;
	        build(a, v*2, tl, tm);
	        build(a, v*2+1, tm+1, tr);
	        //t[v] = t[v*2] + t[v*2+1]; ORIGINAL CHANGED....
	        t[v] = merge(t[v*2], t[v*2+1]);

	    }
	}

	//very confusing
	//n1 always left
	//n2 always right
	//merge child nodes
	Node merge(Node n1, Node n2) {
		int a, b;
		int left = n1.getRValue(); //the rightest value from the left node
		if (left==-1000000) return n2;
		int leftQ = n1.getRQValue();
		int right = n2.getLValue(); //vice versa of left
		if (right==-1000000) return n1;
		int rightQ = n2.getLQValue();
		int max = Math.max(n1.getMax(), n2.getMax());
		if (left==right) {
			if (leftQ+rightQ>max) max = leftQ+rightQ;
		}
		if (n1.getLValue()==right) a=n1.getLQValue()+rightQ;
		else a = n1.getLQValue();
		if (n2.getRValue()==left) b=n2.getRQValue()+leftQ;
		else b = n2.getRQValue();
		return new Node(n1.getLValue(), n2.getRValue(),a,b,max);
	}

	Node search(int v, int tl, int tr, int l, int r) {
		//System.out.println(" v= "+ v +" tl= " + tl + " tr= "+ tr + " l= " + l + " r= " + r);
	    if (l > r) 
	        return new Node(-1000000); //dummy
	    if (l == tl && r == tr) {
	    	//System.out.println("i return " + t[v].getMax());
	        return t[v];

	    }
	    int tm = (tl + tr) / 2;
	    return merge(search(v*2, tl, tm, l, Math.min(r, tm))
	            ,search(v*2+1, tm+1, tr, Math.max(l, tm+1), r));
	}

	/*void update(int v, int tl, int tr, int pos, int new_val) {
	    if (tl == tr) {
	        t[v] = new_val;
	    } else {
	        int tm = (tl + tr) / 2;
	        if (pos <= tm)
	            update(v*2, tl, tm, pos, new_val);
	        else
	            update(v*2+1, tm+1, tr, pos, new_val);
	        t[v] = t[v*2] + t[v*2+1];
	    }
	}*/

	void printArray() {
		for (int i=0;i<4*n;i++) {
			if (t[i]!=null)
				System.out.println("t["+ i+"]= "+t[i].getMax());
		}
	}
}

class uva11235{
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n, q, max, begin, end, count;
		int[] a;
		SegTree s;
		while((n=sc.nextInt())!=0) {

			a = new int[n];
			s = new SegTree(n);

			q = sc.nextInt();
			for (int i=0;i<n;i++) {
				a[i] = sc.nextInt();
			}
			s.build(a,1,0,n-1);
			//s.printArray();
			for (int i=0;i<q;i++) {
				begin = sc.nextInt();
				end = sc.nextInt();
				System.out.println((s.search(1,0,n-1,begin-1, end-1)).getMax());
			}
		}
	}
}