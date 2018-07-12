package section03.task61;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class PrimeNumbersCounterTest {
    @Test public void testSimpleRange() {
        assertEquals(3, PrimeNumbersCounter.createPrimesFilteringStream(2, 5).count());
    }

    @Test public void testBigRange() {
        assertEquals(25, PrimeNumbersCounter.createPrimesFilteringStream(2, 100).count());
    }
}