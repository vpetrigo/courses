package section01.task94;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.stream.Stream;

@DisplayName("Maximum sum of subarray (Kadane's algorithm)")
class TestKadane {
    static class MaxSumExpected {
        private int maxSum;
        private int maxStart;
        private int maxEnd;

        MaxSumExpected(int maxSum, int maxStart, int maxEnd) {
            this.maxSum = maxSum;
            this.maxStart = maxStart;
            this.maxEnd = maxEnd;
        }

        int getMaxSum() {
            return maxSum;
        }

        int getMaxStart() {
            return maxStart;
        }

        int getMaxEnd() {
            return maxEnd;
        }

        @Override
        public String toString() {
            return String.format("MaxSumExpected(maxSum=%d, maxStart=%d, " +
                                 "maxEnd=%d)", maxSum, maxStart, maxEnd);
        }
    }

    @ParameterizedTest(name = "{index} ==> ''{0}''")
    @MethodSource("arrayProvider")
    void testWithArrays(MaxSumExpected expected, int[] arr) {
        Kadane result = Kadane.getSubArrayMaxSum(arr);

        Assertions.assertEquals(expected.getMaxSum(), result.getMaxSum());
        Assertions.assertEquals(expected.getMaxStart(), result.getMaxStart());
        Assertions.assertEquals(expected.getMaxEnd(), result.getMaxEnd());
    }

    static Stream<Arguments> arrayProvider() {
        return Stream.of(Arguments.of(new MaxSumExpected(6, 0, 2),
                                      new int[]{1, 2, 3}), Arguments
                                 .of(new MaxSumExpected(4, 3, 3),
                                     new int[]{2, -2, -1, 4, -5}),
                         Arguments
                                 .of(new MaxSumExpected(-100500, 0, 0),
                                     new int[]{-100500}));
    }
}
