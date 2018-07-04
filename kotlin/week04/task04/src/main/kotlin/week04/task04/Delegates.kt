package week04.task04

import kotlin.properties.ReadWriteProperty
import kotlin.reflect.KProperty
import properties.delegates_how_it_works.MyDate
import properties.delegates_how_it_works.toMillis
import properties.delegates_how_it_works.toDate

class D {
    var date: MyDate by EffectiveDate()
}

class EffectiveDate<R> : ReadWriteProperty<R, MyDate> {

    var timeInMillis: Long? = null

    override fun getValue(thisRef: R, property: KProperty<*>): MyDate {
        return timeInMillis!!.toDate()
    }

    override fun setValue(thisRef: R, property: KProperty<*>, value: MyDate) {
        timeInMillis = value.toMillis()
    }
}

fun main(args: Array<String>) {
    val d = D()

    d.date = MyDate(1990, 1, 1)
    println(d.date)
}
