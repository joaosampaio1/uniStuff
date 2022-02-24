import java.util.*;
import java.lang.*;

//OBJ:Ax+Bsin(x)=C.
//Math.sin(radians)
/*
using bisection algorithm
bisection = divide the function in half using "recursion" to find the x (OBJ)

complexity O(1)
1 since it stops after 100 bisections 
*/
class trigalge {

	static double f(double x) {
		if (x<0) return -x;
		return x;
	}

	static void bisection(int a, int b, int c) {
		int nmax = 100; //max number of resections
		//double tolerance = 0.0000001;
		int n=0;
		double x=0; //mid
		double math;
		double big = 100000.0;
		double small=-100000.0;
		while (n<nmax) {
			x = (big+small)/2;
			//System.out.println(big + " " + small);
			math = a*x+b*Math.sin(x);
			if (math==c) {
				break;
			}
			n++;
			if(math<c) small=x;
			else big=x;
		}
		System.out.printf("%.6f", x);
		System.out.println();

	}

	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		int a, b, c, n;

		n = sc.nextInt();
		for (int i=0;i<n;i++) {
			a=sc.nextInt();
			b=sc.nextInt();
			c=sc.nextInt();
			bisection(a,b,c);
		}

		
	}
}