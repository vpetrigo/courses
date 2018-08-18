package section01.task126;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        int n = reader.nextInt();
        int m = reader.nextInt();
        boolean[][] cinemaRows = new boolean[n][m];

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cinemaRows[i][j] = reader.nextInt() == 1;
            }
        }

        int seatsToBook = reader.nextInt();

        System.out.println(seatChecker(cinemaRows, seatsToBook));
    }

    private static int seatChecker(boolean[][] seats, int seatsToBook) {
        int row = 0;
        int n = seats.length;
        int m = seats[0].length;

        for (int i = 0; i < n; ++i) {
            int count = 0;

            for (int j = 0; j < m; ++j) {
                if (!seats[i][j]) {
                    ++count;
                }
                else {
                    count = 0;
                }

                if (count == seatsToBook) {
                    return i + 1;
                }
            }
        }

        return row;
    }
}
