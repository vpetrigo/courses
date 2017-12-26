import java.util.stream.Stream;
import java.util.Comparator;
import java.util.function.BiConsumer;
import java.util.function.Consumer;

public class FindMinMax {
    public static void main(String[] args) {
        BiConsumer<Integer, Integer> con = (x, y) -> System.out.println(x + y);
        Stream<Integer> int_stream = Stream.of(1, 2, 3);
        Comparator<Integer> comp = Integer::compare;

        findMinMax(int_stream, comp, con);
    }

    public static <T> void findMinMax(
        Stream<? extends T> stream,
        Comparator<? super T> order,
        BiConsumer<? super T, ? super T> minMaxConsumer) {
        MinMaxFinder<T> finder = new MinMaxFinder<>(order);
        stream.forEach(finder);
        minMaxConsumer.accept(finder.min, finder.max);
    // your implementation here
    }

    private static class MinMaxFinder<T> implements Consumer<T> {
        private final Comparator<? super T> order;
        T min;
        T max;

        private MinMaxFinder(Comparator<? super T> order) {
            this.order = order;
        }

        @Override
        public void accept(T t) {
            if (min == null || order.compare(t, min) < 0) {
                min = t;
            }

            if (max == null || order.compare(max, t) < 0) {
                max = t;
            }
        }
    }
}