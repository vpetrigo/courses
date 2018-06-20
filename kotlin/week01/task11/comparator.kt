import java.util.*

fun getList(): List<Int> {
    val arrayList = arrayListOf(1, 5, 2)
    Collections.sort(arrayList, object : Comparator<Int> {
        override fun compare(a: Int, b: Int): Int { return b.compareTo(a) }
    })
    return arrayList
}

fun main(args: Array<String>) {
    println(getList())
}
