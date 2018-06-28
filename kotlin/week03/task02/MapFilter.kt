data class Order(val name: String)

data class Shop(val name: String, val customers: List<Customer>)

data class Customer(val name: String, val city: City, val orders: List<Order>)

data class City(val name: String)

// Return the set of cities the customers are from
fun Shop.getCitiesCustomersAreFrom(): Set<City> = customers.map { it.city }.toSet()

// Return a list of the customers who live in the given city
fun Shop.getCustomersFrom(city: City): List<Customer> = customers.filter { it.city == city }

fun main(args: Array<String>) {
    val shop = Shop("Barber", listOf(Customer("David", City("LA"), listOf(Order(""))),
                                     Customer("Jess", City("PHX"), listOf(Order(""))),
                                     Customer("Ibra", City("LA"), listOf(Order("")))))

    println(shop.getCitiesCustomersAreFrom())
    println(shop.getCustomersFrom(City("LA")))
    println(shop.getCustomersFrom(City("PHX")))
}
