## Task 1

Write a curried form of the function `f(x,y,z)=x+y∗y+z∗z∗z` using lambda expressions
in Java 8 style. The result and `x`, `y`, `z` must be integer numbers.

Solution format. You may write the result in any valid formats but with ; on the end.

An example of a curried function: `x -> y -> ...`;

### Sample Input 1:

```
1 1 1
```

### Sample Output 1:

```
3
```

### Sample Input 2:

```
2 3 4
```

### Sample Output 2:

```
75
```

## Task 2

Write a curried function (using lambdas) that accepts four string
arguments and concatenated all in one string following the rules:

String cases: in the result string, first and second arguments must
be in lower cases and third and fourth in upper cases.
Order of arguments concatenation: first, third, second, fourth.
Solution format. You may write the result in any valid formats but with ; on the end.

An example of a curried function: `x -> y -> ...`;

### Sample Input 1:

```
aa bb cc dd
```

### Sample Output 1:

```
aaCCbbDD
```

### Sample Input 2:

```
AAA bbb CCC ddd
```

### Sample Output 2:

```
aaaCCCbbbDDD
```
