data class City(val name: String)

data class Shop(val name: String, val customers: List<Customer>)

data class Customer(val name: String, val city: City, val orders: List<Order>)

data class Order(val products: List<Product>, val isDelivered: Boolean)

data class Product(val name: String, val price: Double)

// Return the most expensive product among all delivered products
// (use the Order.isDelivered flag)
fun Customer.getMostExpensiveDeliveredProduct(): Product? = orders.filter { it.isDelivered }.flatMap(Order::products).maxBy { it.price }
// Return how many times the given product was ordered.
// Note: a customer may order the same product for several times.
fun Shop.getNumberOfTimesProductWasOrdered(product: Product): Int = customers.flatMap(Customer::orders).flatMap(Order::products).count { it.equals(product) }

fun main(args: Array<String>) {
    val order1 = Order(listOf(Product("socks", 15.99), Product("shave", 49.99)), false)
    val order2 = Order(listOf(Product("socks", 13.99), Product("dress", 677.99)), true)
    val order3 = Order(listOf(Product("jeans", 45.99), Product("scissors", 4.99)), true)
    val order4 = Order(listOf(Product("socks", 15.99)), true)
    val customer1 = Customer("David", City("LA"), listOf(order1, order3))
    val customer2 = Customer("Jess", City("PHX"), listOf(order2, order4))
    val customer3 = Customer("Ivan", City("NY"), listOf(order4, order1))
    val shop = Shop("Walmart", listOf(customer1, customer2, customer3))

    println(customer1.getMostExpensiveDeliveredProduct())
    println(shop.getNumberOfTimesProductWasOrdered(Product("socks", 15.99)))
}
