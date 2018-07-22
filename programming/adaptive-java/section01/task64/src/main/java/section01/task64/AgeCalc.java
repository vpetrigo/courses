package section01.task64;

import java.util.Scanner;

public class AgeCalc {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        String name = reader.next();
        Integer age = reader.nextInt();

        System.out.printf("%s, You will be 100 years old in %d year.", name, 2016 - age + 100);
    }
}
