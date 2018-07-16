package section03.task49;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class BadWordsDetection {
    public static Stream<String> createBadWordsDetectingStream(String text, List<String> badWords) {
        return Arrays.stream(text.split("\\s"))
                .filter(badWords::contains).distinct().sorted();
    }

    public static void main(String[] args) {
        String text = "Hello World My world";

        System.out.println(text);
        System.out.println(createBadWordsDetectingStream(text, List.of("World", "My")).collect(Collectors.toList()));
    }
}
