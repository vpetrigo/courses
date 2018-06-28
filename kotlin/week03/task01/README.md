## Introduction

This part was inspired by [GS Collections Kata][1].

Default collections in Kotlin are Java collections, but there
are lots of useful extension functions for them. For example,
operations that transform a collection to another one, starting
with 'to': [`toSet`][2] or [`toList`][3].

Implement an extension function `Shop.getSetOfCustomers()`.

```kotlin
data class Shop(val name: String, val customers: List<Customer>)

data class Customer(val name: String, val city: City, val orders: List<Order>)
```

[1]: https://github.com/goldmansachs/gs-collections-kata
[2]: https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/kotlin.-iterable/to-set.html
[3]: https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/kotlin.-iterable/to-list.html
