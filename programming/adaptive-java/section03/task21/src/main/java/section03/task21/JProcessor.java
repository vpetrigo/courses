package section03.task21;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;
import java.util.ListIterator;
import java.util.stream.Collectors;

public class JProcessor {
    public static void main(String[] args) throws IOException {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));
        List<String> list = Arrays.stream(reader.readLine().split("\\s+"))
                                  .filter(s -> s.startsWith("J"))
                                  .map(s -> s.replaceFirst("J", ""))
                                  .collect(Collectors.toList());
        ListIterator li = list.listIterator(list.size());

        while (li.hasPrevious()) {
            System.out.println(li.previous());
        }
    }
}
