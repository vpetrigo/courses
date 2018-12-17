package section01.task51;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));
        System.out.println(
                reader.lines().mapToDouble(Double::parseDouble).takeWhile(value -> value != 0).average()
                      .orElse(0.0));
    }
}
