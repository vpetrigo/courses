import java.io.IOException;

public class Main {
    public static final byte CAR_RET  = 13;
    public static final byte NEW_LINE = 10;
    
    public static void main(String[] args) throws IOException {
        int curByte, prevByte;
        prevByte = System.in.read();
        while (prevByte >= 0) {
            curByte = System.in.read();
            if (prevByte != CAR_RET || curByte != NEW_LINE)
                System.out.write(prevByte);
            prevByte = curByte;
        }
        System.out.flush();
    }
}
