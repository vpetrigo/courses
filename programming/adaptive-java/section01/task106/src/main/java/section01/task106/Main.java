package section01.task106;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));

        Integer numLines = Integer.parseInt(reader.readLine());

        List<List<Integer>> datesList = reader.lines().limit(numLines)
                                              .map(s -> Arrays
                                                      .stream(s.split("\\s+"))
                                                      .mapToInt(
                                                              Integer::parseInt)
                                                      .boxed().collect(
                                                              Collectors
                                                                      .toList()))
                                              .sorted((o1, o2) -> {
                                                  assert o1.size() == o2.size();

                                                  for (int i = 0; i < o1.size();
                                                       ++i) {
                                                      int result =
                                                              Integer.compare(
                                                                      o1.get(i),
                                                                      o2.get(i));

                                                      if (result != 0) {
                                                          return result;
                                                      }
                                                  }

                                                  return 0;
                                              }).collect(Collectors.toList());

        datesList.forEach(integers -> System.out.println(
                integers.stream().map(Object::toString)
                        .collect(Collectors.joining(" "))));
    }
}