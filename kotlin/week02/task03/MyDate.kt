data class MyDate(val year: Int, val month: Int, val dayOfMonth: Int) : Comparable<MyDate> {
    override fun compareTo(other: MyDate) = when {
        year != other.year -> year - other.year
        month != other.month -> month - other.month
        else -> dayOfMonth - other.dayOfMonth
    }
}

operator fun MyDate.rangeTo(other: MyDate) = DateRange(this, other)

class DateRange(override val start: MyDate, override val endInclusive: MyDate): ClosedRange<MyDate>

fun checkInRange(date: MyDate, first: MyDate, last: MyDate): Boolean {
    return date in first..last
}

fun main(args: Array<String>) {
    println(checkInRange(MyDate(1900, 1, 1), MyDate(1990, 1, 1), MyDate(2000, 1, 1)))
    println(checkInRange(MyDate(1991, 5, 12), MyDate(1990, 1, 1), MyDate(2000, 1, 1)))
}
