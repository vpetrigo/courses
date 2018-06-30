## Fold

Implement `Shop.getSetOfProductsOrderedByEveryCustomer()` using [`fold`][1].

```kotlin
listOf(1, 2, 3, 4).fold(1, {
    partProduct, element ->
    element * partProduct
}) == 24

data class Shop(val name: String, val customers: List<Customer>)

data class Customer(val name: String, val city: City, val orders: List<Order>)

data class Order(val products: List<Product>, val isDelivered: Boolean)
```

[1]: https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/kotlin.-iterable/fold.html
