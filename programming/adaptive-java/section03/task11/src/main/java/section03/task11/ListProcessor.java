package section03.task11;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.stream.IntStream;

public class ListProcessor {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        LinkedList<Integer> ll = new LinkedList<>();
        Arrays.stream(reader.readLine().split("\\s+")).map(Integer::parseInt)
                .forEach(ll::addFirst);
        //your code
        IntStream.range(0, 3).forEach(e -> ll.remove(0));
        Collections.sort(ll);
        ll.forEach(System.out::println);
    }
}
