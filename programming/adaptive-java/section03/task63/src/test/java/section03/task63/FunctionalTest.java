package section03.task63;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;

import java.util.List;

public class FunctionalTest {
    @Test
    void testExampleOne()
    {
        List<Integer> exampleOne = List.of(1, 1, 1, 1);

        Assertions.assertEquals(List.of(1, 1, 1, 1), Functional.identityTransformation.apply(exampleOne));
        Assertions.assertEquals(List.of(3, 3, 3, 3), Functional.multTwoAndThenAddOneTransformation.apply(exampleOne));
        Assertions.assertEquals(List.of(2, 2, 2, 2), Functional.squareAndThenGetNextEvenNumberTransformation.apply(exampleOne));
    }

    @Test
    void testExampleTwo() {
        List<Integer> exampleTwo = List.of(1, 2, 3);

        Assertions.assertEquals(List.of(1, 2, 3), Functional.identityTransformation.apply(exampleTwo));
        Assertions.assertEquals(List.of(3, 5, 7), Functional.multTwoAndThenAddOneTransformation.apply(exampleTwo));
        Assertions.assertEquals(List.of(2, 6, 10), Functional.squareAndThenGetNextEvenNumberTransformation.apply(exampleTwo));
    }
}
