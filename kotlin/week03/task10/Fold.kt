data class City(val name: String)

data class Shop(val name: String, val customers: List<Customer>)

data class Customer(val name: String, val city: City, val orders: List<Order>)

data class Order(val products: List<Product>, val isDelivered: Boolean)

data class Product(val name: String, val price: Double)

fun moreUndeliveredOrders(orders: List<Order>): Boolean {
    val (delivered, undelivered) = orders.partition { it.isDelivered }
    return undelivered.size > delivered.size
}

// Return the set of products that were ordered by every customer
fun Shop.getSetOfProductsOrderedByEveryCustomer(): Set<Product> {
    val allProducts = customers.flatMap(Customer::orders).flatMap(Order::products).toSet()

    return customers.fold(allProducts, {
        orderedByAll, customer ->
        orderedByAll.intersect(customer.orders.flatMap { it.products }.toSet())
    })
}

fun main(args: Array<String>) {
    val order1 = Order(listOf(Product("socks", 15.99), Product("shave", 49.99)), false)
    val order2 = Order(listOf(Product("socks", 13.99), Product("dress", 677.99)), true)
    val order3 = Order(listOf(Product("jeans", 45.99), Product("scissors", 4.99)), true)
    val order4 = Order(listOf(Product("socks", 15.99)), true)
    val customer1 = Customer("David", City("LA"), listOf(order1, order3))
    val customer2 = Customer("Jess", City("PHX"), listOf(order2, order4))
    val customer3 = Customer("Ivan", City("NY"), listOf(order4, order1))
    val shop = Shop("Walmart", listOf(customer1, customer2, customer3))

    println(shop.getSetOfProductsOrderedByEveryCustomer())
}
