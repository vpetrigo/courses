package section03.task16;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));

        reader.lines().map(string -> string.split(";")).flatMap(Arrays::stream)
              .map(string -> string.split(" ")).map(Arrays::asList)
              .map(x -> x.stream().map(Integer::parseInt)
                         .collect(Collectors.toList())).map(Collections::max)
              .collect(Collectors.toCollection(
                      () -> new TreeSet<>(Collections.reverseOrder())))
              .forEach(System.out::println);
    }
}
