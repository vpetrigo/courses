import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.io.IOException;
import java.io.InputStream;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

public class ByteToString {
    public static void main(String[] args) {
        ByteArrayInputStream test = new ByteArrayInputStream(new byte[]{48, 49, 50, 51});

        try {
            System.out.println(readAsString(test, StandardCharsets.US_ASCII));
        }
        catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public static String readAsString(InputStream inputStream, Charset charset) throws IOException {
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        int block;
        while ((block = inputStream.read()) != -1) {
            outputStream.write(block);
        }
        return new String(outputStream.toByteArray(), charset);
    }
}