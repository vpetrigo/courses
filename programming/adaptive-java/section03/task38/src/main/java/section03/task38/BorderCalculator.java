package section03.task38;

import java.util.function.BiFunction;
import java.util.stream.LongStream;

public class BorderCalculator {
    public static void main(String[] args) {
        BiFunction<Long, Long, Long> function =
                (x, y) -> LongStream.rangeClosed(x, y).reduce(1, (a, b) -> a * b);

        System.out.println(function.apply(0L, 1L));
        System.out.println(function.apply(5L, 15L));
        System.out.println(function.apply(2L, 2L));
    }
}
