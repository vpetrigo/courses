## Extension functions on collections

Kotlin code can be easily mixed with Java code.
Thus in Kotlin we don't introduce our own collections,
but use standard Java ones (slightly improved). Read
about [read-only and mutable views on Java collections][1].

In [Kotlin standard library][2] there are lots of extension functions that make the work with collections more convenient. Rewrite the previous example once more using an extension function [`sortedDescending`][3].

[1]: https://blog.jetbrains.com/kotlin/2012/09/kotlin-m3-is-out/#Collections
[2]: https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/
[3]: https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/kotlin.-iterable/sorted-descending.html