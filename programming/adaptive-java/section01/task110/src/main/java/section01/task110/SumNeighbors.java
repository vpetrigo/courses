package section01.task110;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class SumNeighbors {
    public static List<Integer> sumNeighbors(List<Integer> integerList) {
        if (integerList.size() < 2) {
            return integerList;
        }

        return IntStream.range(0, integerList.size()).map(i -> {
            int l_border = i - 1 >= 0 ? i - 1 : integerList.size() - 1;
            int r_border = i + 1 < integerList.size() ? i + 1 : 0;
            return IntStream
                    .of(integerList.get(l_border), integerList.get(r_border))
                    .sum();
        }).boxed().collect(Collectors.toList());
    }
}
