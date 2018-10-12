package section03.task14;

import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class SymmetricalDifference {
    public static Set<Integer> symDifference(Set<Integer> set1, Set<Integer> set2) {
        return Stream.concat(set1.stream(), set2.stream())
                     .filter(integer -> !(set1.contains(integer) &&
                                          set2.contains(integer)))
                     .collect(Collectors.toSet());
    }
}
