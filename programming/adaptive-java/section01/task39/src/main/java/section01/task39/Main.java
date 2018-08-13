package section01.task39;

import java.util.Scanner;

public class Main {
    static long gcd(long a, long b) {
        if (b == 0) {
            return a;
        }

        return gcd(b, a % b);
    }

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        long a = reader.nextInt();
        long b = reader.nextInt();
        long lcm = (a * b / gcd(a, b));

        System.out.println(lcm);
    }
}
