package section01.task19;

import java.util.Scanner;
import java.util.function.IntPredicate;

public class Main {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        IntPredicate interval = n -> (n > -15 && n <= 12) || (n > 14 && n < 17) || (n >= 19);

        System.out.println(interval.test(reader.nextInt()) ? "True" : "False");
    }
}
