package section03.task14;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.stream.Stream;

class SymmetricalDifferenceTest {
    @ParameterizedTest(name = "run #{index} with [{arguments}]")
    @MethodSource("setProvider")
    void testSymmetricalDifference(Set<Integer> first, Set<Integer> second, Set<Integer> expected) {
        Set<Integer> symmetricDiff =
                SymmetricalDifference.symDifference(first, second);

        Assertions.assertEquals(expected, symmetricDiff);
    }

    private static Stream<Arguments> setProvider() {
        return Stream.of(Arguments.of(new HashSet<>(Arrays.asList(1, 2, 3, 4)),
                                      new HashSet<>(Arrays.asList(3, 4, 5, 6)),
                                      new HashSet<>(Arrays.asList(1, 2, 5, 6))),
                         Arguments.of(new HashSet<>(
                                 Arrays.asList(3, 14, 16, 5, 13, 2, 20, 10, 6,
                                               9)), new HashSet<>(
                                 Arrays.asList(2, 4, 6, 8, 10, 12, 14, 16, 18,
                                               20)), new HashSet<>(
                                 Arrays.asList(3, 4, 5, 8, 9, 12, 13, 18))),
                         Arguments.of(new HashSet<>(Arrays.asList(1, 2)),
                                      new HashSet<>(Arrays.asList(2, 3)),
                                      new HashSet<>(Arrays.asList(1, 3))));
    }
}
