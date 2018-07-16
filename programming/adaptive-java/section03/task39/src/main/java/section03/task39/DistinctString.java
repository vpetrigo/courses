package section03.task39;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.function.Function;

public class DistinctString {
    public static List<String> uniqueStrings(List<String> strings, Function<List<String>, List<String>> filterFun) {
        return filterFun.apply(strings);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        List<String> listOfStrings = List.of(reader.readLine().split("\\s+"));
        List<String> unique = uniqueStrings(listOfStrings, (slist) -> new ArrayList<>(new HashSet<>(slist)));
        System.out.println(unique);
    }
}
