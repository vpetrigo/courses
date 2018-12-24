## Spliterator

On `spliteratorWork(List<Double> lst)`:

- using `Spliterator` add to `List<Double>` sqrts all square roots of items from
`lst`, if this item greater than `1`
- use `Math.sqrt(number)` to find square root: `Math.sqrt(4) -> 2.0`

On `print(List<Double> list)`:

- get `spliterator()` of given list
- divide spliterator into 2 parts (use `spliterator.trySplit()`)
- print all items which `>= 2` from first part (use `.println()`)
- print empty string
- print all items which `>= 10` from second part (use `.println()`)

*Remember when you use `trySplit()` method*:

```java
List<Integer> lst = new ArrayList<>(Arrays.asList(1,1,1,2,2,2,2));

Spliterator<Integer> split = lst.spliterator();
split.trySplit()...//-> 1 1 1 (its your first path of spliterator)
split...//2 2 2 2 (now split contains of second path)
```

### Sample Input:

```
4 4 4 100 100 100
```

### Sample Output:

```
2.0
2.0
2.0

10.0
10.0
10.0
```
