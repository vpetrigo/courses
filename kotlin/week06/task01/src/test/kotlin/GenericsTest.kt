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
}
