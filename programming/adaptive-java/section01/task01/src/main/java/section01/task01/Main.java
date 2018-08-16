package section01.task01;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        // put your code here
        Scanner reader = new Scanner(System.in);
        int squirrels = reader.nextInt();
        int nuts = reader.nextInt();

        System.out.println(nuts / squirrels);
    }
}
