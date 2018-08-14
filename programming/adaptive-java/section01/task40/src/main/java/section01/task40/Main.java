package section01.task40;

import java.util.Scanner;
import java.util.stream.IntStream;

public class Main {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);

        System.out.println(IntStream.generate(reader::nextInt).limit(reader.nextInt()).filter(n -> n % 4 == 0).max().getAsInt());
    }
}
