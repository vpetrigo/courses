package week06.task01

import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions.assertEquals

class GenericsTest {
    @Test fun testPartitionToList() {
        val (words, lines) = listOf("a", "a b", "c", "d e").
            partitionTo(ArrayList<String>(), ArrayList()) { s -> !s.contains(" ") }
        assertEquals(words, listOf("a", "c"))
        assertEquals(lines, listOf("a b", "d e"))
    }

    @Test fun testPartitionToHashSet() {
        val (letters, other) = setOf('a', '%', 'r', '}').
            partitionTo(HashSet<Char>(), HashSet()) { c -> c in 'a'..'z' || c in 'A'..'Z'}
        assertEquals(letters, setOf('a', 'r'))
        assertEquals(other, setOf('%', '}'))
    }
}
