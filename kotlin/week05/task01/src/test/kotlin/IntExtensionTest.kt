package week05.task01

import org.junit.Assert.assertEquals
import org.junit.Test

class TestDelegatesHowItWorks {
    @Test fun testTask() {
        val expected: List<Boolean> = listOf(false, true, true)

        assertEquals(expected, task())
    }
}
