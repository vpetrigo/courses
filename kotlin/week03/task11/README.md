## Compound tasks

Implement `Customer.getMostExpensiveDeliveredProduct()`
and `Shop.getNumberOfTimesProductWasOrdered()` using functions
from the Kotlin standard library.

```kotlin
data class Shop(val name: String, val customers: List<Customer>)

data class Customer(val name: String, val city: City, val orders: List<Order>)

data class Order(val products: List<Product>, val isDelivered: Boolean)

data class Product(val name: String, val price: Double)
```
