import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.function.Function;

public class PopularWords {
    public static void main(String[] args) {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(System.in))) {
            in.lines().flatMap(str -> Stream.of(str.split("[\\p{Blank}\\p{Punct}]+"))).map(String::toLowerCase)
            .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()))
            .entrySet().stream()
            .sorted((e0, e1) -> {
                int res = e1.getValue().compareTo(e0.getValue());
                return res == 0 ? e0.getKey().compareTo(e1.getKey()) : res;
            }).limit(10).forEach(x -> System.out.println(x.getKey()));
        }
        catch (IOException e) {
            
        }
    }
}