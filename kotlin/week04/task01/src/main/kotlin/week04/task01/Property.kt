package week04.task01

class PropertyExample() {
    var counter = 0
    var propertyWithCounter: Int? = null
        set(value) {
            ++counter
            field = value
        }
}

fun main(args: Array<String>) {
    val prop = PropertyExample()

    println("prop.counter: ${prop.counter}, prop.propertyWithCounter: ${prop.propertyWithCounter}")
    prop.propertyWithCounter = 10
    println("prop.counter: ${prop.counter}, prop.propertyWithCounter: ${prop.propertyWithCounter}")
    prop.propertyWithCounter = 20
    println("prop.counter: ${prop.counter}, prop.propertyWithCounter: ${prop.propertyWithCounter}")
}
