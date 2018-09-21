package section01.task110;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

class Main {
    public static void main(String[] args) {
        try (BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in))) {
            List<Integer> integerList = Arrays.stream(reader.readLine().split(
                    "\\s++")).map(Integer::parseInt).collect(Collectors
                    .toList());
            List<Integer> integers = SumNeighbors.sumNeighbors(integerList);

            System.out.println(integers.stream().map(Object::toString).collect(Collectors.joining(" ")));
        }
        catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
