package week05.task02

import java.util.HashMap

fun <K, V> buildMap(builder: MutableMap<K, V>.() -> Unit): Map<K, V> {
    val newMap = mutableMapOf<K, V>()
    
    newMap.builder()
    return newMap
}

fun usage(): Map<Int, String> {
    return buildMap {
        put(0, "0")
        for (i in 1..10) {
            put(i, "$i")
        }
    }
}

fun main(args: Array<String>) {
    println(usage())
}
