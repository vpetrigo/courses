Run-length encoding is the basic algorithm of data compression.

In this problem, we will implement one of its simplest versions.

On the input, the algorithm has a string containing the characters of the Latin
alphabet. This string is split into the groups of consecutive identical
characters ("series"). The repetitive symbol and the number of repetitions
characterize each series. It is the information that is recorded into the code:
first written the run-length of the repeating symbols, then the symbol itself.
We will omit the number or repetitions for the series one symbol long.

For example, let’s take the string

```
aaabccccCCaB
```

Let us break it down into series

```
aaa b cccc CC a B
```

After which we encode the series and receive the summary line
that and we will consider the result of algorithm operation.

```
3ab4c2CaB
```

### Input format:

Single string containing the arbitrary charaters of the Latin alphabet.

### Output format:

The string containing a coded sequence.

### Sample Input 1:

```
aaabccccCCaB
```

### Sample Output 1:

```
3ab4c2CaB
```

### Sample Input 2:

```
a
```

### Sample Output 2:

```
a
```
