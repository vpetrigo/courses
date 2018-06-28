## Filter; map

Implement extension functions `Shop.getCitiesCustomersAreFrom()`
and `Shop.getCustomersFrom()` using functions [`map`][1] and [`filter`][2].

```kotlin
val numbers = listOf(1, -1, 2)
numbers.filter { it > 0 } == listOf(1, 2)
numbers.map { it * it } == listOf(1, 1, 4)

data class Shop(val name: String, val customers: List<Customer>)

data class Customer(val name: String, val city: City, val orders: List<Order>)

data class City(val name: String)
```

[1]: https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/kotlin.-iterable/map.html
[2]: https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/kotlin.-iterable/filter.html