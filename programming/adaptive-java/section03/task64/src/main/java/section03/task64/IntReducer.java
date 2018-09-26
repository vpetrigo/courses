package section03.task64;

import java.util.function.BiFunction;
import java.util.function.IntBinaryOperator;

public class IntReducer {
    /**
     * The operator combines all values in the given range into one value
     * using combiner and initial value (seed)
     */
    public static final BiFunction<Integer, IntBinaryOperator, IntBinaryOperator>
            reduceIntOperator =
            (seed, intBinaryOperator) -> (left, right) -> {
                int accum = seed;

                for (int i = left; i <= right; ++i)
                {
                    accum = intBinaryOperator.applyAsInt(accum, i);
                }

                return accum;
            };

    /**
     * The operator calculates the sum in the given range (inclusively)
     */
    public static final IntBinaryOperator sumOperator =
            reduceIntOperator.apply(0, Integer::sum);

    /**
     * The operator calculates the product in the given range (inclusively)
     */
    public static final IntBinaryOperator productOperator =
            reduceIntOperator.apply(1, (x, y) -> x * y);
}
