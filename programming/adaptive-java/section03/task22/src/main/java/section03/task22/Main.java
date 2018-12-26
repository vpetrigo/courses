package section03.task22;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;
import java.util.Spliterator;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));
        List<Double> list = Arrays.stream(reader.readLine().split("\\s+"))
                                  .mapToDouble(Double::parseDouble).boxed()
                                  .collect(Collectors.toList());

        list = spliteratorWork(list);
        print(list);
    }

    public static List<Double> spliteratorWork(List<Double> lst) {
        return lst.stream().filter(num -> num > 1.0).map(Math::sqrt)
                  .collect(Collectors.toList());
    }

    public static void print(List<Double> list) {
        Spliterator<Double> splitSecond = list.spliterator();
        Spliterator<Double> splitFirst = splitSecond.trySplit();
        Function<Double, Consumer<Double>> processor = compNum -> (num) -> {
            if (num >= compNum) {
                System.out.println(num);
            }
        };

        splitFirst.forEachRemaining(processor.apply(2.0));
        System.out.println();
        splitSecond.forEachRemaining(processor.apply(10.0));
    }
}
