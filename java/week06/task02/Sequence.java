import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Deque;
import java.util.ArrayDeque;

public class Sequence {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int index = 0;
        String numLine;
        Deque<Integer> queue = new ArrayDeque<>();

        while (index != -1 && (numLine = br.readLine()) != null) {
            for (String numStr : numLine.split("\\s")) {
                try {
                    int num = Integer.parseInt(numStr);

                    if ((index++ % 2) != 0)
                    {
                        queue.addFirst(num);
                    }
                }
                catch (NumberFormatException ex) {
                    index = -1;
                    break;
                }
            }
        }

        queue.forEach(elem -> { System.out.printf("%d ", elem); });
    }
}