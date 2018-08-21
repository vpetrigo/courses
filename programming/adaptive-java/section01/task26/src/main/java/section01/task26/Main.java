package section01.task26;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        int x1 = reader.nextInt();
        int y1 = reader.nextInt();
        int x2 = reader.nextInt();
        int y2 = reader.nextInt();

        System.out.println((x1 == x2 || y1 == y2 || Math.abs(x1 - x2) == Math.abs(y1 - y2)) ? "YES" : "NO");
    }
}
