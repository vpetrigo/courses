package section01.task142;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.stream.Stream;

public class Main {
    public static void main(String[] args) {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));

        System.out.println(Stream.generate(() -> {
            try {
                return reader.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }

            return "0";
        }).takeWhile(s -> !s.equals("0")).mapToInt(Integer::parseInt).sum());
    }
}
