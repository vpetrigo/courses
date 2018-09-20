package section03.task63;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.function.Function;
import java.util.function.IntUnaryOperator;
import java.util.function.UnaryOperator;
import java.util.stream.Collectors;

public class Functional {
    /**
     * The function accepts a list of mappers and returns an operator that accepts a list of integers
     * and sequentially applies each mapper to each value (perform a transformation)
     */
    public static final Function<List<IntUnaryOperator>, UnaryOperator<List<Integer>>> multifunctionalMapper =
            intUnaryOperators -> nums -> {
                IntUnaryOperator resultOp = IntUnaryOperator.identity();

                for (IntUnaryOperator op : intUnaryOperators) {
                    resultOp = resultOp.andThen(op);
                }

                List<Integer> mapList = new ArrayList<>();

                for (Integer elem : nums) {
                    mapList.add(resultOp.applyAsInt(elem));
                }

                return mapList;
            };

    public static final Function<List<IntUnaryOperator>, UnaryOperator<List<Integer>>> multifunctionalMapperStream =
            intUnaryOperators -> nums -> nums.stream().map(num -> intUnaryOperators.stream()
                    .reduce(IntUnaryOperator.identity(), IntUnaryOperator::andThen)
                    .applyAsInt(num)).collect(Collectors.toList());

    /**
     * EXAMPLE: the operator transforms each number to the same number (perform the identity transformation)
     * <p>
     * It returns a list of the same numbers.
     */
    public static final UnaryOperator<List<Integer>> identityTransformation =
            multifunctionalMapper.apply(Arrays.asList(x -> x, x -> x, x -> x));

    /**
     * The operator accepts an integer list.
     * It multiplies by two each integer number and then add one to its.
     * <p>
     * The operator returns transformed integer list.
     */
    public static final UnaryOperator<List<Integer>> multTwoAndThenAddOneTransformation = multifunctionalMapper.apply(Arrays.asList(x -> x * 2, x -> x + 1));

    /**
     * The operator accepts an integer list.
     * It squares each integer number and then get the next even number following it.
     * <p>
     * The operator returns transformed integer list.
     */
    public static final UnaryOperator<List<Integer>> squareAndThenGetNextEvenNumberTransformation = multifunctionalMapper.apply(Arrays.asList(x -> x * x, x -> (x + 2) % 2 == 0 ? x + 2 : x + 1));

    public static void main(String[] args) {
        IntUnaryOperator increment = a -> a + 1;
        IntUnaryOperator multiplyTwo = a -> a * 2;
        List<IntUnaryOperator> operatorList = Arrays.asList(increment, multiplyTwo);
        UnaryOperator<List<Integer>> composition = multifunctionalMapper.apply(operatorList);

        System.out.println(composition.apply(List.of(1, 1, 1, 1)));
        System.out.println(multTwoAndThenAddOneTransformation.apply(List.of(1, 1, 1, 1)));
        System.out.println(Functional.class.getCanonicalName());
    }
}
