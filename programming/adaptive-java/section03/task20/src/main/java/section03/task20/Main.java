package section03.task20;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;
import java.util.ListIterator;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));
        List<String> list = Arrays.asList(reader.readLine().split("\\s"));

        solution1(list);
        solution2(list);
        solution3(list);
    }

    public static void solution1(List<String> list) {
        list.forEach(s -> {
            System.out.println(s);

            if (s.equals("Hip")) {
                System.out.println("Hop");
            }
        });
    }

    public static void solution2(List<String> list) {
        ListIterator<String> listIterator = list.listIterator();

        while (listIterator.hasNext())
        {
            String currentString = listIterator.next();
            System.out.println(currentString);

            if (currentString.equals("Hip"))
            {
                System.out.println("Hop");
            }
        }
    }

    public static void solution3(List<String> list) {
        for (String string : list)
        {
            System.out.println(string);

            if (string.equals("Hip"))
            {
                System.out.println("Hop");
            }
        }
    }
}
