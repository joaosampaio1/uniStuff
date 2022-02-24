import java.util.*;
/*
this exercise is to simply remove an put elements in data structure
so i just created the data structure and did the tasks in every data structure
and made sure it behave proprely using flags for each data structure

complexity O(nlogn)
n=number of operations

logn is because of priorityQueue

*/
class uva11995 {
	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		Queue<Integer> q = new LinkedList<Integer>();
		Stack<Integer> s = new Stack<Integer>();
		PriorityQueue<Integer> p = new PriorityQueue<Integer>(Collections.reverseOrder());
		int c, x, n;
		int flagQ, flagS, flagP;

		while (sc.hasNextInt()) {
			flagQ = flagS = flagP = 1;
			q.clear();
			s.clear();
			p.clear();
			n = sc.nextInt();
			for (int i=0;i<n;i++) {
				c = sc.nextInt();
				x=sc.nextInt();
				//System.out.println(c+" "+x);
				if (c==1) {
					q.add(x);
					s.add(x);
					p.add(x);
				}
				else {
					if (c==2) {
						//System.out.println("x "+x+ " pQueue " +p.peek()+" queue "+q.element()+" stack "+s.peek());
						if (q.isEmpty() || x!=q.remove()) flagQ = 0;
						if (s.isEmpty() || x!=s.pop()) flagS = 0;
						if (p.isEmpty() || x!=p.remove()) flagP = 0;
					}
				}
			}
			//System.out.println(flagP+" "+flagQ+" "+flagS);
			if (flagP+flagQ+flagS>1) System.out.println("not sure");
			else if (flagP+flagQ+flagS==0) System.out.println("impossible");
			else if (flagP==1) System.out.println("priority queue");
			else if (flagQ==1) System.out.println("queue");
			else if (flagS==1) System.out.println("stack");
		}
	}
}