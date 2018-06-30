package task03

fun joinOptions(options: Collection<String>) = options.joinToString(prefix="[", postfix="]")

fun main(args: Array<String>) {
    println(joinOptions(listOf("a", "b", "c")))
}
