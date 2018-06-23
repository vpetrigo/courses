##In range

In Kotlin `in` checks are translated to the corresponding `contains` calls:

```kotlin
val list = listOf("a", "b")
"a" in list  // list.contains("a")
"a" !in list // !list.contains("a")


data class MyDate(val year: Int, val month: Int, val dayOfMonth: Int) : Comparable<MyDate>
```

Read about [ranges][1]. Add a method `fun contains(d: MyDate)` to the `class DateRange`
to allow in checks with a range of dates.

[1]: https://kotlinlang.org/docs/reference/ranges.html
