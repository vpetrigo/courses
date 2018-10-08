package section03.task89;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
import java.util.Arrays;
import java.util.Objects;
import java.util.stream.Stream;

public class ComparatorInspector {
    /**
     * Return Type variable that corresponds to the type parameterizing Comparator.
     *
     * @param clazz {@link Class} object, should be non null
     * @return {@link Type} object or null if Comparable does not have type parameter
     */
    public static <T extends Comparable<?>> @Nullable Type getComparatorType(@NotNull Class<T> clazz) {
        // Add implementation
        return Stream.of(clazz.getGenericInterfaces())
                     .filter(ParameterizedType.class::isInstance)
                     .map(type -> (ParameterizedType) type)
                     .filter(parameterizedType -> Objects
                             .equals(parameterizedType.getRawType()
                                                      .getTypeName(),
                                     Comparable.class.getCanonicalName()))
                     .flatMap(type -> Arrays
                             .stream(type.getActualTypeArguments()))
                     .findFirst().orElse(null);
    }
}
