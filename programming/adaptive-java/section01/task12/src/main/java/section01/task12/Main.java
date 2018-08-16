package section01.task12;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);

        System.out.println(new StringBuilder(reader.nextLine()).reverse().toString());
    }
}
