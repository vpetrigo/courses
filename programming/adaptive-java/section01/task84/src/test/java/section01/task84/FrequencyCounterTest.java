package section01.task84;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;

import java.util.List;

public class FrequencyCounterTest {
    @Test
    void testValidArray() {
        List<Integer> numList = List.of(2, 3, 9, 2, 2);

        Assertions.assertTrue(FrequencyCounter.hasMajority(numList));
    }

    @Test
    void testInvalidArray() {
        List<Integer> numList = List.of(2, 3, 9, 2);

        Assertions.assertFalse(FrequencyCounter.hasMajority(numList));
    }
}
