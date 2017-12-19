import java.util.function.Predicate;
import java.util.Objects;
import java.util.function.Function;

public class Ternary {
    public static void main(String[] args) {
        Predicate<Object> condition = Objects::isNull;
        Function<Object, Integer> ifTrue = obj -> 0;
        Function<CharSequence, Integer> ifFalse = CharSequence::length;
        Function<String, Integer> safeStringLength = ternaryOperator(condition, ifTrue, ifFalse);

        System.out.println(safeStringLength.apply("Test"));
        System.out.println(safeStringLength.apply(null));
    }

    public static <T, U> Function<T, U> ternaryOperator(Predicate<? super T> condition, Function <? super T, ? extends U> ifTrue, Function<? super T, ? extends U> ifFalse) {
        return str -> condition.test(str) ? ifTrue.apply(str) : ifFalse.apply(str);
    }
}