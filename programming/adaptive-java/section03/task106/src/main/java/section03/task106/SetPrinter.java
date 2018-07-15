package section03.task106;

import java.util.Arrays;
import java.util.Set;
import java.util.TreeSet;

public class SetPrinter {
    public static void main(String[] args) {
        Set<String> nameSet = new TreeSet<>(Arrays.asList("Mr.Green", "Mr.Yellow", "Mr.Red"));

        nameSet.forEach(System.out::println);
    }
}
