Write three functions:

1. Multifunctional mapper (transformer) that accepts a list of operators (mappers) and returns a new operator. The
returned operator accepts a list of integer numbers and sequentially applies each mapper to each number in the list
(performs multiple transformations).
2. In terms of the multifunctional mapper define an operator that multiplies by two each integer number and then add one
to its. The operator is applied to each number in the input list.
3. In terms of the multifunctional mapper define an operator that squares each integer number and then calculates the
next even number following it. The operator is also applied to each number in the input list.

Try not to use Stream API. Write the mapper yourself. To simplify the problem all function (represented by objects)
are declared, you need to finish their realization.
 
Look carefully at definition of each function. Also there is an example: identity operator that is defined in terms
of the multifunctional mapper. It doesn't changes values in the input list.

During testing all operators will be tested (including identity).

**Example 1**. An input list with integer numbers `[1, 1, 1, 1]`:

 - `identityTransformation` returns the result list `[1, 1, 1, 1]`.
 - `multTwoAndThenAddOneTransformation` returns the result list `[3, 3, 3, 3]`.
 - `squareAndThenGetNextEvenNumberTransformation` returns the result list `[2, 2, 2, 2]`.

**Example 2**. An input list with integer numbers `[1, 2, 3]`.

 - `identityTransformation` returns the result list `[1, 2, 3]`.
 - `multTwoAndThenAddOneTransformation` returns the result list `[3, 5, 7]`.
 - `squareAndThenGetNextEvenNumberTransformation` returns the result list `[2, 6, 10]`.
