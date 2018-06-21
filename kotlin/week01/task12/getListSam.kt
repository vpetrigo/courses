import java.util.*

fun getList(): List<Int> {
    val arrayList = arrayListOf(1, 5, 2)
    Collections.sort(arrayList, { x, y -> y.compareTo(x) })
    return arrayList
}

fun getListExplicit(): List<Int> {
    val arrayList = arrayListOf(1, 5, 2)
    Collections.sort(arrayList, Comparator<Int> { x, y -> y.compareTo(x) })
    return arrayList
}

fun main(args: Array<String>) {
    println(getList())
    println(getListExplicit())
}
