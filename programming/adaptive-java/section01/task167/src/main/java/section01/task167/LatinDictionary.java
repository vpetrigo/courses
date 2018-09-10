package section01.task167;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class LatinDictionary {
    public static Map<String, List<String>> getLatinDictionary(Map<String, List<String>> toLatinDictionary) {
        Map<String, List<String>> latinDictionary = new HashMap<>();

        toLatinDictionary.forEach((key, value) -> value.forEach(
                entry -> {
                    if (!latinDictionary.containsKey(entry)) {
                        latinDictionary.put(entry, new ArrayList<>());
                    }

                    latinDictionary.get(entry).add(key);
                }
        ));

        latinDictionary.forEach((key, value) -> Collections.sort(value));

        return latinDictionary;
    }

    public static void main(String[] args) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            int lines = Integer.parseInt(reader.readLine());
            Map<String, List<String>> toLatinDict = new HashMap<>();

            reader.lines().limit(lines).forEach(line -> {
                String[] array = line.split(" - ");
                String key = array[0];
                List<String> values = Arrays.asList(array[1].split(", "));

                toLatinDict.put(key, values);
            });

            Map<String, List<String>> dict = getLatinDictionary(toLatinDict);

            System.out.println(dict.size());
            dict.entrySet().stream().sorted(Comparator.comparing(Map.Entry::getKey))
                    .forEach(entry -> System.out.printf("%s - %s\n", entry.getKey(),
                            String.join(", ", entry.getValue())));
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}
