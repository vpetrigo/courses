package section03.task50;

import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Main {
    public static IntStream createFilteringStream(IntStream evenStream, IntStream oddStream) {
        return IntStream.concat(evenStream, oddStream).filter(i -> i % 3 == 0 && i % 5 == 0).sorted().skip(2);
    }

    public static void main(String[] args) {
        IntStream oddStream = IntStream.builder().add(75).build();
        IntStream evenStream = IntStream.builder().add(30).add(60).add(90).build();
        IntStream concatStream = createFilteringStream(oddStream, evenStream);

        System.out.println(concatStream.boxed().collect(Collectors.toList()));
    }
}
