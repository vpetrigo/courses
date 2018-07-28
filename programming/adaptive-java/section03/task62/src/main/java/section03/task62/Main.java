package section03.task62;

import java.util.function.Function;

public class Main {
    public static void main(String[] args) {
        Function<Long, Function<Long, Function<Long, Long>>> fun = x -> y -> z -> x + y * y + z * z * z;

        System.out.println(fun.apply(1L).apply(2L).apply(3L));
    }
}
