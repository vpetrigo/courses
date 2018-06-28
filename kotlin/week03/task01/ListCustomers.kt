data class Order(val name: String)

data class Shop(val name: String, val customers: List<Customer>)

data class Customer(val name: String, val city: String, val orders: List<Order>)

fun Shop.getSetOfCustomers(): Set<Customer> = customers.toSet()

fun main(args: Array<String>) {
    val shop = Shop("Barber", listOf(Customer("David", "LA", listOf(Order(""))),
                                     Customer("Jess", "PHX", listOf(Order("")))))

    println(shop.getSetOfCustomers())
}

