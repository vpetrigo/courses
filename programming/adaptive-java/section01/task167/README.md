Once, while looking through the old books in the attic, schoolboy Mike found the Spanish-Latin dictionary.
By that time, his knowledge of Spanish was perfect and his dream was to learn Latin. Therefore, his discovery
was very useful.

Unfortunately, this one dictionary is not enough to learn the language: besides the Spanish-Latin dictionary,
he needs a Latin-Spanish one. In the absence of better, he decided to make the second dictionary from the first one.

As it is well known, any dictionary consists of translated words, each of which has a few words-translations. For
each of the Latin words, which are present somewhere in the dictionary, Mike offers to find all of their translations
(i.e. all the Spanish words, for which our Latin word was specified in the list of its translations), and consider
only such words the translations of the particular Latin word.

Help Mike to complete the task on creation of the Latin-Spanish dictionary from the Spanish-Latin one.

### Input data

The first line contains the only integer number `N` that is the number of Spanish words in the dictionary. Then `N`
descriptions follow: each of the descriptions is located in a separate line, where first goes a Spanish word, next
goes the space separated dash (symbol number 45), and then go the translations of this Spanish word into Latin,
separated by spaces and commas. Translations are sorted in the lexicographic order. The order of the Spanish words
in the dictionary is also lexicographic.

All words consist of only the lowercase Latin letters; length of each word does not exceed `15` characters. The total
number of words at the input is not greater than `100000`.

### Output data

Output the Latin-Spanish dictionary, corresponding to the given one, strictly observing the format of the input
data. In particular, the first should be the translation of a lexicographically minimal Latin word, further - the
second in this order, etc. Spanish words inside the translation must also be sorted in a lexicographic order.

### Sample Input:

```
3
apple - malum, pomum, popula
fruit - baca, bacca, popum
punishment - malum, multa
```

### Sample Output:

```
7
baca - fruit
bacca - fruit
malum - apple, punishment
multa - punishment
pomum - apple
popula - apple
popum - fruit
```
