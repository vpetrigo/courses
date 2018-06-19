fun containsEven(collection: Collection<Int>): Boolean = collection.any { num: Int -> num % 2 == 0 }

fun main(args: Array<String>) {
    val collect1 = listOf(1, 2, 3)
    val collect2 = listOf(1, 1, 1)

    println("collect1 has even: ${containsEven(collect1)}")
    println("collect2 has even: ${containsEven(collect2)}")
}
