Write three operators:

A reduce operator that accepts an initial value (seed) and a combiner function
and then returns a new function that combines all values in the given integer
range (inclusively) into one integer value (it's a simple form of reduction). 

- In terms of the reduce operator define a sum operator for summing integer 
values in the given range.
- In terms of the reduce operator define a product operator for multiplying 
integer values in the given range. 

Try not to use Stream API. Write the reducer yourself.

To simplify the problem all functions are declared, you need to finish their
realization. 

Look carefully at definition of each operator.

During testing all three operators will be tested. The **left boundary <= the 
right boundary**.

*Example 1.* `Left boundary = 1, right boundary = 4.`

- `sumOperator` returns the result `10`.
- `productOperator` returns the result `24`.

*Example 2.* `Left boundary = 5, right boundary = 6.`

- `sumOperator` returns the result `11`.
- `productOperator` returns the result `30`.

﻿If the task is too hard for you, see theory lesson on currying,
URL: [https://stepik.org/lesson/Returning-functions-and-currying-35160/step/1
?course=Java-Functional-progr...﻿][1]

[1]: https://stepik.org/lesson/Returning-functions-and-currying-35160/step/1?course=Java-Functional-programming&unit=14551
