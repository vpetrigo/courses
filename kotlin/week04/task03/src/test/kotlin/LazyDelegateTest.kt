package week04.task03

import org.junit.Assert.assertEquals
import org.junit.Assert.assertNotNull
import org.junit.Assert.assertNull
import org.junit.Test

class LazyDelegateTest {
    @Test fun testLaziness() {
        var counter: Int = 0
        val initializer: () -> Int = {
            ++counter
            42 
        }
        val lazyProp = LazyProperty(initializer)

        assertEquals(counter, 0)
        assertEquals(lazyProp.lazyValue, 42)
        assertEquals(counter, 1)
        assertEquals(lazyProp.lazyValue, 42)
        assertEquals(counter, 1)
    }
}
