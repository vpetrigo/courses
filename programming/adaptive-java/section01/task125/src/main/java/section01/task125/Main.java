package section01.task125;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scr = new Scanner(System.in);
        int size = scr.nextInt();

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (i == j || i == size - j - 1 || i == size / 2 ||
                    j == size / 2) {
                    star();
                }
                else {
                    dot();
                }

                if (j == size - 1) {
                    enter();
                }
                else {
                    space();
                }
            }
        }
    }

    private static void star() {
        System.out.print("*");
    }

    private static void dot() {
        System.out.print(".");
    }

    private static void space() {
        System.out.print(" ");
    }

    private static void enter() {
        System.out.println();
    }
}
