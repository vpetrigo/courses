package section01.task123;

import javafx.util.Pair;

import java.util.Scanner;

public class MatrixMax {
    public static Pair<Integer, Integer> matrixMaxElementPosition(int[][] matrix) {
        int rows = matrix.length;
        int cols = matrix[0].length;
        int max = matrix[0][0];
        int max_r = 0;
        int max_c = 0;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (max < matrix[i][j])
                {
                    max = matrix[i][j];
                    max_r = i;
                    max_c = j;
                }
            }
        }

        return new Pair<>(max_r, max_c);
    }

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        int rows = reader.nextInt();
        int cols = reader.nextInt();
        int[][] matrix = new int[rows][cols];

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                matrix[i][j] = reader.nextInt();
            }
        }

        Pair<Integer, Integer> result = matrixMaxElementPosition(matrix);

        System.out.printf("%d %d\n", result.getKey(), result.getValue());
    }
}
