package section01.task119;

import java.util.Arrays;
import java.util.Scanner;
import java.util.function.Function;
import java.util.stream.Collectors;

public class ListRepeat {
    public static void main(String[] args) {
        Arrays.stream((new Scanner(System.in)).nextLine().split("\\s+"))
                .map(Integer::parseInt)
                .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()))
                .forEach((number, count) -> {
                    if (count > 1) {
                        System.out.print(number + " ");
                    }
                });
    }
}
