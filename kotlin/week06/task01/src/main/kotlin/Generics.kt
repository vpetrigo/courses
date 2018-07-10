package week06.task01

import java.util.*

fun <T, C : MutableCollection<in T>> Collection<T>.partitionTo(first: C, second: C, predicate: (T) -> Boolean) : Pair<C, C> = partition(predicate).let { it.first.toCollection(first) to it.second.toCollection(second) }

fun partitionWordsAndLines() {
    val (words, lines) = listOf("a", "a b", "c", "d e").
            partitionTo(ArrayList<String>(), ArrayList()) { s -> !s.contains(" ") }
    words == listOf("a", "c")
    lines == listOf("a b", "d e")
}

fun partitionLettersAndOtherSymbols() {
    val (letters, other) = setOf('a', '%', 'r', '}').
            partitionTo(HashSet<Char>(), HashSet()) { c -> c in 'a'..'z' || c in 'A'..'Z'}
    letters == setOf('a', 'r')
    other == setOf('%', '}')
}

fun main(args: Array<String>) {
    partitionWordsAndLines()
    partitionLettersAndOtherSymbols()
}