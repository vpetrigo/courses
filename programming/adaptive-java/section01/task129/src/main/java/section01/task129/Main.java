package section01.task129;

import java.util.Scanner;

public class Main {
    public static class Matrix {
        private int[][] array;
        private int width;
        private int height;

        Matrix(int width, int height) {
            this.width = width;
            this.height = height;
            array = new int[width][height];
        }

        private void setElement(int i, int j, int value) {
            array[i][j] = value;
        }

        public int getElement(int i, int j) {
            return array[i][j];
        }

        Matrix rotateRight() {
            Matrix matrix = new Matrix(getHeight(), getWidth());
            for (int i = 0; i < getWidth(); i++) {
                for (int j = 0; j < getHeight(); j++) {
                    matrix.setElement(j, getWidth() - 1 - i, getElement(i, j));
                }
            }

            return matrix;
        }

        @Override
        public String toString() {
            StringBuilder builder = new StringBuilder();
            for (int i = 0; i < getWidth(); i++) {
                for (int j = 0; j < getHeight(); j++) {
                    builder.append(String.format("%s ", array[i][j]));
                }
                builder.append(System.lineSeparator());
            }

            return builder.toString();
        }

        public int getWidth() {
            return width;
        }

        public int getHeight() {
            return height;
        }
    }

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        int n = reader.nextInt();
        int m = reader.nextInt();
        Matrix matrix = new Matrix(n, m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                matrix.setElement(i, j, reader.nextInt());
            }
        }

        System.out.println(matrix.rotateRight());
    }
}
