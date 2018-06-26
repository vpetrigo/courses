class Invokable {
    var numberOfInvocations: Int = 0
        private set
    operator fun invoke(): Invokable {
        ++numberOfInvocations
        return this
    }
}

fun invokeTwice(invokable: Invokable) = invokable()()

fun main(args: Array<String>) {
    val inv1 = Invokable()
    invokeTwice(inv1)
    println(inv1.numberOfInvocations)
}
