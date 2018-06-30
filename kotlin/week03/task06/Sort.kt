data class City(val name: String)

data class Shop(val name: String, val customers: List<Customer>)

data class Customer(val name: String, val city: City, val orders: List<Order>)

data class Order(val products: List<Product>, val isDelivered: Boolean)

data class Product(val name: String, val price: Double)

// Return a list of customers, sorted by the ascending number of orders they made
fun Shop.getCustomersSortedByNumberOfOrders(): List<Customer> = customers.sortedBy { it.orders.size }

fun main(args: Array<String>) {
    val order1 = Order(listOf(Product("socks", 15.99), Product("shave", 49.99)), false)
    val order2 = Order(listOf(Product("socks", 13.99), Product("dress", 677.99)), true)
    val order3 = Order(listOf(Product("jeans", 45.99), Product("scissors", 4.99)), true)
    val customer1 = Customer("David", City("LA"), listOf(order1, order3))
    val customer2 = Customer("Jess", City("PHX"), listOf(order2))
    val customer3 = Customer("Ivan", City("NY"), listOf())
    val shop = Shop("Walmart", listOf(customer1, customer2, customer3))

    shop.getCustomersSortedByNumberOfOrders().forEach { print("${it.name} ") }
}
