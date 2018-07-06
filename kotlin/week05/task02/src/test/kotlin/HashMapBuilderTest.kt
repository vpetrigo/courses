package week05.task02

import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions.assertEquals

class HashMapBuilderTest {
    @Test fun testMapBuilderIntString() {
        val map: Map<Int, String> = buildMap {
            put(0, "0")
            for (i in 1..3) {
                put(i, "$i")
            }
        }

        val expectedMap = mapOf(0 to "0", 1 to "1", 2 to "2", 3 to "3")

        assertEquals(expectedMap, map)
    }

    @Test fun testMapBuilderIntInt() {
        val map: Map<Int, Int> = buildMap {
            put(0, 0)
            for (i in 1..3) {
                put(i, i)
            }
        }

        val expectedMap = mapOf(0 to 0, 1 to 1, 2 to 2, 3 to 3)

        assertEquals(expectedMap, map)
    }
}
