package week05.task01

fun task(): List<Boolean> {
    val isEven: Int.() -> Boolean = { this % 2 == 0 }
    val isOdd: Int.() -> Boolean = { !isEven() }

    return listOf(42.isOdd(), 239.isOdd(), 294823098.isEven())
}

fun main(args: Array<String>) {
    println(task())
}
