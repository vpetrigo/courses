package section03.task77;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class ListMultiplicatorTest {
    @Test
    void testNormalMultiplication() {
        List<Integer> integerList = new ArrayList<>(Arrays.asList(1, 2, 3));
        List<Integer> expected = Arrays.asList(1, 2, 3, 1, 2, 3);

        ListMultiplicator.multiply(integerList, 2);
        Assertions.assertEquals(expected, integerList);
    }

    @Test
    void testZeroNumberofMultiplication() {
        List<Integer> integerList = new ArrayList<>(Arrays.asList(1, 2, 3));
        List<Integer> expected = new ArrayList<>();

        ListMultiplicator.multiply(integerList, 0);
        Assertions.assertEquals(expected, integerList);
    }
}
