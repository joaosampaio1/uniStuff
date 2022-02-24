import java.util.*;

/*
complexity O(mlogn)
m=number of rounds of the fight to reach the conclusion
n=number of leemings
*/

/*
every leeming with the same power is equal
if a leeming 50 fights a 10 it becomes equal to a 40, so we just add his quant
this is so we can sort the leeming power to decrease the complexity
*/
class Leeming implements Comparable<Leeming>{
	int power;
	int quant;

	Leeming(int power) {
		this.power = power;
		this.quant = 1;
	}

	int getPower() { return power; } 
	int getQuant() { return quant; } 
	int incrQuant() {this.quant++; return quant;}
	int decrQuant() {this.quant--; return quant;}

	 @Override
    public int compareTo(Leeming l) {
        int p1 = getPower();
        int p2 = l.getPower();
        if (p1<p2) return 1;
        if (p1>p2) return -1;
        return 0; //not reachable
    }
}

class uva978 {

	//search using power, since its whats wanted
	static Leeming searchLeeming(SortedSet<Leeming> s, int power) {
		for (Leeming leeming : s) {
			if(leeming.getPower()==power) return leeming;
		}
		return null;
	}

	/*
	logistic of a round
	we remove or decrease the quantity of the leemings that going to fight
	they fight
	add them to a different list, to not be used again in the same round
	and then re add them again to the sorted set using addLeeming
	*/

	static void fight(int battle,SortedSet<Leeming> green,SortedSet<Leeming> blue) {
		int g, b;
		Leeming lg, lb;
		LinkedList<Integer> blist = new LinkedList<Integer>();
		LinkedList<Integer> glist = new LinkedList<Integer>();
		//System.out.println("NEW FIGHT");
		for (int i=0;i<battle;i++) {
			if (green.isEmpty() || blue.isEmpty()) break;
			lg = green.first();
			lb = blue.first();
			//System.out.println("GREEN = " + lg.getPower() + " VS BLUE = " + lb.getPower());
			//System.out.println("GREENQUANT = " + lg.getQuant() + " VS BLUEQUANT = " + lb.getQuant());
			if(lg.decrQuant()==0) green.remove(lg);
			if(lb.decrQuant()==0) blue.remove(lb);
			g=lg.getPower()-lb.getPower();
			b=lb.getPower()-lg.getPower();
			if (g>0) glist.add(g);
			if (b>0) blist.add(b);
		}
		for (int i: blist) addLeeming(blue,i);
		for (int i: glist) addLeeming(green,i);
	}

	//this adds the leeming to set or increases the quantity
	static void addLeeming(SortedSet<Leeming> s, int power) {
		Leeming l;
		l = searchLeeming(s, power);
		if (l==null) {
			//System.out.println("I ADD " + power);
			s.add(new Leeming(power));
		}
		else l.incrQuant();
	}

	//debug
	static void printSet(SortedSet<Leeming> s) {
		int quant;
		for (Leeming leeming : s) {
			quant = leeming.getQuant();
			for (int i=0;i<quant;i++) {
				System.out.println(leeming.getPower());
			}
		}
	}

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		int c = sc.nextInt();
		int b, ngreen, nblue;

		//we going to sort using the power
		Comparator comparator = new Comparator<Leeming>() {
			@Override
			public int compare(Leeming l1, Leeming l2) {
			    return l1.compareTo(l2);
			}
		};

		SortedSet<Leeming> green = new TreeSet<Leeming>(comparator); 
		SortedSet<Leeming> blue = new TreeSet<Leeming>(comparator); 

		for (int i=0;i<c;i++) {
			
			b = sc.nextInt();
			ngreen = sc.nextInt();
			nblue = sc.nextInt();
			for (int j=0;j<ngreen;j++) {
				addLeeming(green,sc.nextInt());
			}
			for (int j=0;j<nblue;j++) {
				addLeeming(blue,sc.nextInt());
			}

			//printSet(blue);
			//printSet(green);


			while (!green.isEmpty() && !blue.isEmpty()) {
				fight(b,green,blue);
				//System.out.println("stuck here??");
			}
			//prints
			if (green.isEmpty() && blue.isEmpty()) {
				System.out.println("green and blue died");
			}
			else {
				if (green.isEmpty()) {
					System.out.println("blue wins");
					printSet(blue);
				}
				if (blue.isEmpty()) {
					System.out.println("green wins");
					printSet(green);
				}
			}

			//reset set
			if (i!=c-1) System.out.println();
			green = new TreeSet<Leeming>(comparator);
			blue = new TreeSet<Leeming>(comparator);
		}
	} 
}