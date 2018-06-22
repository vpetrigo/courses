import java.util.GregorianCalendar

data class MyDate(val year: Int, val month: Int, val dayOfMonth: Int) : Comparable<MyDate> {
    override fun compareTo(other: MyDate) = GregorianCalendar(year, month, dayOfMonth).compareTo(GregorianCalendar(other.year, other.month, other.dayOfMonth))
}

fun compare(date1: MyDate, date2: MyDate) = date1 < date2

fun main(args: Array<String>) {
    println(compare(MyDate(1902, 1, 1), MyDate(1901, 12, 31)))
}
