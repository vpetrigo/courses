package section03.task62;

import java.util.function.Function;

public class Main {
    public static Function<Long, Function<Long, Function<Long, Long>>> getMathFun() {
        return x -> y -> z -> x + y * y + z * z * z;
    }

    public static Function<String, Function<String, Function<String, Function<String, String>>>> getStringFun() {
        return a -> b -> c -> d -> a.toLowerCase() + c.toUpperCase() + b.toLowerCase() + d.toUpperCase();
    }

    public static void main(String[] args) {
        Function<Long, Function<Long, Function<Long, Long>>> fun = getMathFun();

        System.out.println(fun.apply(1L).apply(2L).apply(3L));

        Function<String, Function<String, Function<String, Function<String, String>>>> strFun = getStringFun();

        System.out.println(strFun.apply("aa").apply("bb").apply("cc").apply("dd"));
    }
}
