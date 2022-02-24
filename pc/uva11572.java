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

class e11572 {
    /*
    i use a map to save the snowflake and the last position
    we iterate throught the snowflakes and increase the size of the
    current package if its not repeated in the same package
    if its repeated we see if the current package is bigger than the
    bigest so far, if so, the new bigest is the current package

    complexity/test O(n)
    n=number of snowflake
    it just iterates through the list
    */
	public static void main(String[] args) {

		Reader sc = new Reader();
		Map<Integer,Integer> m = new HashMap<Integer,Integer>();
		int pos = 0;
		int n = 0;
		int snowflake = 0;
		int tmpmax = 0;
		int max = 0;
		int cases = 0;
		try {cases = sc.nextInt(); } catch (IOException e){}
		for(int i=0;i<cases;i++) {
			try { n = sc.nextInt(); } catch (IOException e){}
			for (int j=0;j<n;j++) {
				try { snowflake = sc.nextInt(); } catch (IOException e){}
				if (m.get(snowflake)==null) {
					m.put(snowflake,j);
					tmpmax++;
				}
				else {
					pos = m.get(snowflake);
					if (j-pos>tmpmax) tmpmax++;
					else tmpmax = j-pos;
					m.replace(snowflake, j);
				}
				if (tmpmax>max) max=tmpmax;
			}
			System.out.println(max);
			max = tmpmax = 0;
			m.clear();
		}
	}
}