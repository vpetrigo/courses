import section01.task94.MatrixMaxSum;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));
        List<Integer> matrixParams =
                Arrays.stream(reader.readLine().split("\\s+"))
                      .map(Integer::parseInt).collect(Collectors.toList());
        int[][] matrix = new int[matrixParams.get(0)][matrixParams.get(1)];

        for (int[] row : matrix) {
            System.arraycopy(Arrays.stream(reader.readLine().split("\\s+"))
                                   .mapToInt(Integer::parseInt).toArray(), 0,
                             row, 0, row.length);
        }

        System.out.println(MatrixMaxSum.findMaxSum(matrix).getMaxSum());
    }
}
