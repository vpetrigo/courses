## Partition

Implement `Shop.getCustomersWithMoreUndeliveredOrdersThanDelivered()` using [`partition`][1].

```kotlin
val numbers = listOf(1, 3, -4, 2, -11)
val (positive, negative) = numbers.partition { it > 0 }
positive == listOf(1, 3, 2)
negative == listOf(-4, -11)

data class Shop(val name: String, val customers: List<Customer>)

data class Customer(val name: String, val city: City, val orders: List<Order>)

data class Order(val products: List<Product>, val isDelivered: Boolean)
```

Note that [destructuring declaration][2] syntax is used in this example.

[1]: https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/kotlin.-iterable/partition.html
[2]: https://kotlinlang.org/docs/reference/multi-declarations.html
