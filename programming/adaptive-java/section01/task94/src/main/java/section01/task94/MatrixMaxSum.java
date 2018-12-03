package section01.task94;

import org.jetbrains.annotations.NotNull;

import java.util.Arrays;

public class MatrixMaxSum {
    static public class Result {
        long maxSum;
        long leftBound;
        long rightBound;
        long topBound;
        long bottomBound;

        Result(int initial) {
            this.maxSum = initial;
        }

        void updateResult(long maxSum, long leftBound, long rightBound, long topBound, long bottomBound) {
            this.maxSum = maxSum;
            this.leftBound = leftBound;
            this.rightBound = rightBound;
            this.topBound = topBound;
            this.bottomBound = bottomBound;
        }

        public long getMaxSum() {
            return maxSum;
        }
    }

    static public Result findMaxSum(@NotNull int[][] matrix) {
        int rows = matrix.length;
        int columns = matrix[0].length;
        int[] intermediateSum = new int[rows];
        Result result = new Result(matrix[0][0]);

        for (int left = 0; left < columns; ++left) {
            Arrays.fill(intermediateSum, 0);

            for (int right = left; right < columns; ++right) {
                for (int i = 0; i < rows; ++i) {
                    intermediateSum[i] += matrix[i][right];
                }

                Kadane kadaneResult = Kadane.getSubArrayMaxSum(intermediateSum);

                if (kadaneResult.getMaxSum() > result.maxSum) {
                    result.updateResult(kadaneResult.getMaxSum(), left, right,
                                        kadaneResult.getMaxStart(),
                                        kadaneResult.getMaxEnd());
                }
            }
        }

        return result;
    }
}
