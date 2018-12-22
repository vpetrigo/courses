package section01.task59;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));
        String pythonVariableName = reader.readLine();

        System.out.println(Arrays.stream(pythonVariableName.split("_"))
                                 .map(String::toLowerCase)
                                 .map(s -> s.substring(0, 1).toUpperCase() +
                                           s.substring(1))
                                 .collect(Collectors.joining()));
    }
}
