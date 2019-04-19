package section01.task71;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class ReplaceTest {
    @ParameterizedTest
    @ValueSource(strings = {"my file name.txt", "string     with        multi" +
                                                " spaces", "single"})
    void testReplace(String line) {
        assertEquals(line.replaceAll("\\s+", "_"),
                     Replace.spaceReplace(line));
    }
}
