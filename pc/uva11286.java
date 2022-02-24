import java.util.*;
import java.io.*;

class Reader {
	//FAST SCANNER FROM GEEKSFORGEEKS
	//https://www.geeksforgeeks.org/fast-io-in-java-in-competitive-programming/
        final private int BUFFER_SIZE = 1 << 16;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;
 
        public Reader()
        {
            din = new DataInputStream(System.in);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
 
        public Reader(String file_name) throws IOException
        {
            din = new DataInputStream(
                new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
 
        public String readLine() throws IOException
        {
            byte[] buf = new byte[64]; // line length
            int cnt = 0, c;
            while ((c = read()) != -1) {
                if (c == '\n') {
                    if (cnt != 0) {
                        break;
                    }
                    else {
                        continue;
                    }
                }
                buf[cnt++] = (byte)c;
            }
            return new String(buf, 0, cnt);
        }
 
        public int nextInt() throws IOException
        {
            int ret = 0;
            byte c = read();
            while (c <= ' ') {
                c = read();
            }
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
 
            if (neg)
                return -ret;
            return ret;
        }
 
        public long nextLong() throws IOException
        {
            long ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (neg)
                return -ret;
            return ret;
        }
 
        public double nextDouble() throws IOException
        {
            double ret = 0, div = 1;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
 
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
 
            if (c == '.') {
                while ((c = read()) >= '0' && c <= '9') {
                    ret += (c - '0') / (div *= 10);
                }
            }
 
            if (neg)
                return -ret;
            return ret;
        }
 
        private void fillBuffer() throws IOException
        {
            bytesRead = din.read(buffer, bufferPointer = 0,
                                 BUFFER_SIZE);
            if (bytesRead == -1)
                buffer[0] = -1;
        }
 
        private byte read() throws IOException
        {
            if (bufferPointer == bytesRead)
                fillBuffer();
            return buffer[bufferPointer++];
        }
 
        public void close() throws IOException
        {
            if (din == null)
                return;
            din.close();
        }
}

class e11286 {
    /*
    The solution is to put the sorted combination of the courses in a map
    with key being the combination and value how many time it occurs
    then we search the most popular (the max value) and remove the keys with value inferior
    ... this is in case there is more than 1 combination
    the map values becomes a collection of the values, since the combination itself doesnt matter anymore
    to print the solution we simply get the size of the collection (amount of popular combinations ) and multiply it
    with max value (number of students)  

    the complexity of each test should be O(nlogn)
    -searches the map for the combination while it adds new combinations
    -sorting doesnt add to the complexity since its always size 5
    n=amount of combinations
    */
	public static void main(String[] args) {

		Reader sc = new Reader(); //using this fastscanner we need to catch the exception
		Map<String,Integer> m = new HashMap<String,Integer>();
		int X = 5;
		int n = 0;
		try { n = sc.nextInt(); } catch (IOException e){};
		int c[] = new int[X];
		String s;

		while (n>0) { //while more tests
			for (int i=0;i<n;i++) {
				for (int j=0;j<X;j++) {
					try { c[j] = sc.nextInt(); } catch (IOException e){};
				}
				Arrays.sort(c); 
				s=Arrays.toString(c);
                System.out.println(s);
				if(m.get(s) == null) m.put(s,1);
                else m.replace(s,m.get(s)+1);
			}
            Collection<Integer> coll = m.values();
            int max = Collections.max(coll);
            coll.removeIf(a->(a<max)); //remove all values less than the max 
            System.out.println(max*coll.size());
			m.clear();
			try { n = sc.nextInt(); }catch (IOException e){}; //re-read
		}
	}
}
