import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

/**
 * SymDiff
 */
public class SymDiff {
    public static void main(String[] args) {
        Set<Integer> c = symmetricDifference(Set.of(1, 2, 3), Set.of(0, 1, 2));

        for (Integer elem : c) {
            System.out.println(elem);
        }
    }

    public static <T> Set<T> symmetricDifference(Set<? extends T> set1, Set<? extends T> set2) {
        Set<T> result = new HashSet<>(set1);

        set2.forEach(item -> { if (!result.contains(item)) result.add(item); else result.remove(item); });

        return result;
    }
}