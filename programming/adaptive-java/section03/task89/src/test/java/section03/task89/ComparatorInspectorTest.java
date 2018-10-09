package section03.task89;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.stream.Stream;

class ComparatorInspectorTest {
    @ParameterizedTest(name = "run #{index} -> {arguments}")
    @MethodSource("classProvider")
    void testComparatorInspector(@NotNull Class<? extends Comparable<?>> clazz, @Nullable Type expected) {
        Assertions.assertEquals(expected,
                                ComparatorInspector.getComparatorType(clazz));
    }

    @NotNull
    private static Stream<Arguments> classProvider() {
        return Stream.of(Arguments.of(MyInt.class, Integer.class),
                         Arguments.of(Integer.class, Integer.class),
                         Arguments.of(ArrayList.class, null),
                         Arguments.of(String.class, String.class),
                         Arguments.of(Object.class, null));
    }
}
