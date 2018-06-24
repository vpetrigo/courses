## For loop

Kotlin [for loop][1] iterates through anything
that provides an iterator. Make the class `DateRange`
implement [`Iterable<MyDate>`][2], so that it could be iterated
over. You can use the function `MyDate.nextDay()`.

```kotlin
data class MyDate(val year: Int, val month: Int, val dayOfMonth: Int) : Comparable<MyDate>
```

[1]: https://kotlinlang.org/docs/reference/control-flow.html#for-loops
[2]: https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/kotlin.-iterable/