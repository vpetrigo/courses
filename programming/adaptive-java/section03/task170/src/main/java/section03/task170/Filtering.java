package section03.task170;

import java.util.List;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class Filtering {
    public static <T> List<T> filter(List<T> elems, Predicate<T> predicate) {
        return elems.stream().filter(predicate).collect(Collectors.toList());
    }
}
