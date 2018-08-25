You have two `IntStream`. The first stream contains even numbers and the second
stream contains odd numbers. Create the third stream that contains numbers from
both streams which is divisible by `3` and `5`. After calling `collect(Collectors.toList())`
the stream should return sorted list (ascending) of these numbers. Two first suitable
numbers in the sorted list must be skipped.

**Important.** You need return a prepared `IntStream` from a template method,
not a list of integers. Pay attention to the method template. Do not change the
signature of this method.

### Sample Input 1:

```
1 2 3 4
```
 
### Sample Output 1:

```
[]
```

### Sample Input 2:

```
30 75 60 90
```

### Sample Output 2:

```
[75, 90]
```
