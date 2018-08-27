package section03.task50;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.Arrays;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class MainTest {
    @Test
    void testFilter() {
        IntStream oddStream = IntStream.builder().add(75).build();
        IntStream evenStream = IntStream.builder().add(30).add(60).add(90).build();
        IntStream concatStream = Main.createFilteringStream(oddStream, evenStream);

        Assertions.assertEquals(Arrays.asList(75, 90),
                concatStream.boxed().collect(Collectors.toList()));
    }
}
