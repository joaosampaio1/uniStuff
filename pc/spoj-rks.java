import java.util.*;

class Number implements Comparable<Number> {
	int quant;
	int x; //this is the actual number itself
	int pos;

	Number(int quant, int x, int pos) {
		this.quant = quant;
		this.x = x;
		this.pos = pos;
	}

	int getPos() {return pos;}
	int getQuant() {return quant;}
	int getX() {return x;}
	void incrQuant() {quant++;}
	void setPos(int pos) {this.pos=pos;}
	void setQuant(int quant) {this.quant=quant;}
	void setX(int x) {this.x=x;}

	public int compareTo(Number n2) {
		
		int quant1 = getQuant();
	    int quant2 = n2.getQuant();
	    int pos1 = getPos();
	    int pos2 = n2.getPos();
	    
	    if(quant1==0) return 1;

		if (quant1==quant2) {
	      	if (pos1>pos2) return 1;
	      	return -1;
	      }
	    if (quant1<quant2) return 1;
	    if (quant1>quant2) return -1;
	    return 0;
	}

	public static Comparator<Number> NumberComparator 
                          = new Comparator<Number>() {

	    public int compare(Number n1, Number n2) {
	    	
	   		if(n1==null) return 1;
	   		if(n2==null) return -1;	
	      return n1.compareTo(n2);
	    }
	};
}

class rks {

	/*
	i create an object that saves the quantity and the position of each number
	to sort it using a custom comparator using those two variables

	complexity O(mlogn)
	n=number of different numbers in the code
	m=size of code
	*/

	//search for v in arraylist
	static int get(ArrayList<Number> a, int v) {
		int i=0;
		for (Number number:a) {
			if (v==number.getX()) return i;
			i++;
		}
		return -1;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int c = sc.nextInt();
		//int[] a = new int[c+1];
		//Number[] out = new Number[c+1];
		ArrayList<Number> a = new ArrayList<Number>();
		int x=0;
		int quant=0;
		int tmp;
		boolean flag = false;

		//read
		for (int i=0;i<n;i++) {
			x=sc.nextInt();
			tmp = get(a,x);
			if (tmp==-1) a.add(new Number(1,x,i));
			else a.get(tmp).incrQuant();
		}

		//prints
		a.sort(Number.NumberComparator);
		for (Number number : a) {
			//if (flag == true) System.out.print(" ");
			flag = true;
			tmp = number.getQuant();
			for (int i=0;i<tmp;i++) {
				System.out.print(number.getX());
				if (flag == true) System.out.print(" ");
			}
		}
		System.out.println();
	}
}