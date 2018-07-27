package section03.task45;

import java.util.List;
import java.util.function.IntPredicate;

public class Disjunct {
    /**
     * The method represents a disjunct operator for a list of predicates.
     * For an empty list it returns the always false predicate.
     */
    public static IntPredicate disjunctAll(List<IntPredicate> predicates) {
        return predicates.stream()
                .reduce(IntPredicate::or).orElse(i -> false);
    }

    public static void main(String[] args) {
        List<IntPredicate> predicateList = List.of(((x) -> x > 2), ((x) -> x > 3));

        IntPredicate predicate = disjunctAll(predicateList);
        System.out.println(predicate.test(4));
        System.out.println(predicate.test(2));
    }
}
