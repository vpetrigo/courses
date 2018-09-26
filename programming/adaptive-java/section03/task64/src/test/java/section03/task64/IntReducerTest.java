package section03.task64;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class IntReducerTest {
    @Test
    void testSumOperator() {
        Assertions.assertEquals(10, IntReducer.sumOperator.applyAsInt(1, 4));
        Assertions.assertEquals(11, IntReducer.sumOperator.applyAsInt(5, 6));
    }

    @Test
    void testProductOperator() {
        Assertions.assertEquals(24, IntReducer.productOperator.applyAsInt(1, 4));
        Assertions.assertEquals(30, IntReducer.productOperator.applyAsInt(5, 6));
    }
}
