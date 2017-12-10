import java.io.IOException;

public class Main {
    public static final byte CR  = '\r';
    public static final byte LF = '\n';
    private static boolean last_cr = false;
    
    public static void main(String[] args) throws IOException {
        byte[] in_buf = new byte[1024];
        byte[] out_buf = new byte[1025];
        int read_bytes = 0;

        while ((read_bytes = System.in.read(in_buf, 0, in_buf.length)) > 0)
        {
            int len = convertToUnixLineEnd(in_buf, read_bytes, out_buf);
            System.out.write(out_buf, 0, len);
        }

        System.out.flush();
    }

    private static int convertToUnixLineEnd(byte[] in_arr, int length, byte[] out_arr) {
        assert(in_arr.length <= out_arr.length);
        int j = 0;

        if (last_cr && in_arr[0] != LF) {
            out_arr[j++] = CR;
        }

        last_cr = false;

        for (int i = 0; i < length; ++i) {
            if (in_arr[i] != CR || (i + 1 != length && in_arr[i + 1] != LF)) {
                out_arr[j++] = in_arr[i];
            }
            else
            {
                if (i + 1 == in_arr.length)
                {
                    last_cr = true;
                }
            }
        }

        return j;
    }
}
