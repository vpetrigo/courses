package section03.task20;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));
        List<String> list = Arrays.asList(reader.readLine().split("\\s"));

        list.forEach(s -> {
            System.out.println(s);

            if (s.equals("Hip")) {
                System.out.println("Hop");
            }
        });
    }
}
