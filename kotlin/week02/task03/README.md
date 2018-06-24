## Range to

Implement the function `MyDate.rangeTo()`. This allows
you to create a range of dates using the following syntax:

```kotlin
MyDate(2015, 5, 11)..MyDate(2015, 5, 12)
```

Note that now the class `DateRange` implements the standard
[`ClosedRange`][1] interface and inherits `contains` method implementation.

[1]: https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.ranges/kotlin.-closed-range/index.html