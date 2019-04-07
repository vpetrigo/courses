package section01.task114;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));
        String[] tokens = reader.readLine().split("(?<=(.))(?!\\1)");
        String result =
                Arrays.stream(tokens).map(s -> s.length() + s.substring(0, 1))
                      .collect(Collectors.joining())
                      .replaceAll("(?<!\\d)1(?!\\d)", "");
        System.out.println(result);
    }
}
