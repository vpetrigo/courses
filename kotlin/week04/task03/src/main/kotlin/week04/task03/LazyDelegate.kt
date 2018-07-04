package week04.task03

class LazyProperty(val initializer: () -> Int) {
    val lazyValue: Int by lazy(initializer)
}

fun main(args: Array<String>) {
    val lazyProp = LazyProperty { 42 }

    println("lazyProp.lazyValue: ${lazyProp.lazyValue}")
}
