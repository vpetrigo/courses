data class MyDate(val year: Int, val month: Int, val dayOfMonth: Int) : Comparable<MyDate> {
    override fun compareTo(other: MyDate) = when {
        year != other.year -> year - other.year
        month != other.month -> month - other.month
        else -> dayOfMonth - other.dayOfMonth
    }
}

class DateRange(val start: MyDate, val endInclusive: MyDate) {
    operator fun contains(d: MyDate) = start <= d && d <= endInclusive
}

fun checkInRange(date: MyDate, first: MyDate, last: MyDate): Boolean {
    return date in DateRange(first, last)
}

fun main(args: Array<String>) {
    println(checkInRange(MyDate(2014, 1, 1), MyDate(2000, 1, 1), MyDate(2020, 1, 1)))
    println(checkInRange(MyDate(2014, 1, 1), MyDate(2021, 12, 31), MyDate(2020, 1, 1)))
}
