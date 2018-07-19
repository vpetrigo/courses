package section03.task51;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class StreamFactorialTest {
    @Test void testFactorialZero() {
        Assertions.assertEquals(1, StreamFactorial.factorial(0));
    }

    @Test void testFactorialOne() {
        Assertions.assertEquals(1, StreamFactorial.factorial(1));
    }

    @Test void testFactorialTwo() {
        Assertions.assertEquals(2, StreamFactorial.factorial(2));
    }

    @Test void testFactorialThree() {
        Assertions.assertEquals(6, StreamFactorial.factorial(3));
    }
}
