package section01.task110;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class SumNeighborsTest {
    @Test
    void testLongArraySum() {
        List<Integer> integerList = Arrays.asList(1, 3, 5, 6, 10);
        List<Integer> expectedList = Arrays.asList(13, 6, 9, 15, 7);

        Assertions.assertEquals(expectedList,
                SumNeighbors.sumNeighbors(integerList));
    }

    @Test
    void testShortArraySum() {
        List<Integer> integerList = Arrays.asList(10, 10);
        List<Integer> expectedList = Arrays.asList(20, 20);

        Assertions.assertEquals(expectedList,
                SumNeighbors.sumNeighbors(integerList));
    }

    @Test
    void testArrayWithOneElement() {
        List<Integer> integerList = Collections.singletonList(10);
        List<Integer> expectedList = Collections.singletonList(10);

        Assertions.assertEquals(expectedList,
                SumNeighbors.sumNeighbors(integerList));
    }
}
