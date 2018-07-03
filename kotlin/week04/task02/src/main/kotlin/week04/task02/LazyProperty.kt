package week04.task02

class LazyProperty(val initializer: () -> Int) {
    private var _lazy: Int? = null
    val lazy: Int
        get() {
            if (_lazy == null)
            {
                _lazy = initializer()
            }

            return _lazy!!
        }
}

fun main(args: Array<String>) {
    val lazy = LazyProperty { 42 }

    println(lazy.lazy)
}
