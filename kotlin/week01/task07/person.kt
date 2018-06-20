data class Person(val name:String, val age:Int)

fun getPeople(): List<Person> {
    return listOf(Person("Alice", 29), Person("Bob", 31))
}

fun main(args: Array<String>) {
    val person1 = Person("Jackson", 15);
    println(person1.name)
    println(getPeople())
}
