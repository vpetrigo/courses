## Sum

Implement `Customer.getTotalOrderPrice()` using [`sum`][1] or [`sumBy`][2].

```kotlin
listOf(1, 5, 3).sum() == 9
listOf("a", "b", "cc").sumBy { it.length() } == 4

data class Customer(val name: String, val city: City, val orders: List<Order>)

data class Order(val products: List<Product>, val isDelivered: Boolean)

data class Product(val name: String, val price: Double)
```

If you want to sum the double values, use [`sumByDouble`][3].

[1]: https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/kotlin.-iterable/sum.html
[2]: https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/kotlin.-iterable/sum-by.html
[3]: https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/kotlin.-iterable/sum-by-double.html
