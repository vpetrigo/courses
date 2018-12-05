package section01.task94;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.stream.Stream;

class TestMatrixMaxSum {
    @ParameterizedTest(name = "{index} ==> ''{0}''")
    @MethodSource("matrixProvider")
    void testMatrixMaxSum(int expected_sum, int[][] matrix) {
        MatrixMaxSum.Result result = MatrixMaxSum.findMaxSum(matrix);

        Assertions.assertEquals(expected_sum, result.maxSum);
    }

    static Stream<Arguments> matrixProvider() {
        return Stream.of(Arguments.of(17, new int[][]{{1, -2, 3}, {4, 5, 6}}),
                         Arguments.of(-100500, new int[][]{{-100500}}));
    }
}
