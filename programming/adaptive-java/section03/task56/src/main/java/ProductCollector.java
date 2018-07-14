package section03.task56;

import java.util.List;
import java.util.stream.Collectors;

public class ProductCollector {
    public static void main(String[] args) {
        List<Integer> numbers = List.of(2, 3, 4);
        long val = numbers.stream().collect(Collectors.reducing(1, (a, b) -> a * a * b * b));

        System.out.println(val);
    }
}
