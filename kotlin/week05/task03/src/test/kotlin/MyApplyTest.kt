package week05.task03

import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions.assertEquals

class MyApplyTest {
    @Test fun testCreateString() {
        val expected = StringBuilder().apply {
            append("Numbers: ")
            for (i in 1..10) {
                append(i)
            }
        }.toString()
        val result = createString()

        assertEquals(expected, result)
    }

    @Test fun testCreateMap() {
        val expected = hashMapOf<Int, String>().apply {
            put(0, "0")
            for (i in 1..10) {
                put(i, "$i")
            }
        }
        val result = createMap()

        assertEquals(expected, result)
    }
}
