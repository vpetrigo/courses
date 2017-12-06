import java.io.InputStream;
import java.io.ByteArrayInputStream;
import java.io.IOException;

public class CheckSum {
    public static void main(String[] args) {
        System.out.println(args);
        byte[] arr = {0x33, 0x45, 0x01};
        ByteArrayInputStream bas = new ByteArrayInputStream(arr);
        try {
            System.out.println(checkSumOfStream(bas));
        }
        catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }

    public static int checkSumOfStream(InputStream inputStream) throws IOException {
        int checkSum = 0;
        int num = -1;

        while ((num = inputStream.read()) != -1) {
            checkSum = num ^ Integer.rotateLeft(checkSum, 1);
        }

        return checkSum;
    }
}