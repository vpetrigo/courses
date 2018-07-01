package week04.task01

import org.junit.Assert.assertEquals
import org.junit.Assert.assertNotNull
import org.junit.Assert.assertNull
import org.junit.Test

class PropertyExampleTest {
    @Test fun testSetter() {
        val prop = PropertyExample()

        assertNull(prop.propertyWithCounter)
        assertEquals(prop.counter, 0)
        prop.propertyWithCounter = 10
        assertNotNull(prop.propertyWithCounter)
        assertEquals(prop.propertyWithCounter, 10)
        assertEquals(prop.counter, 1)
        prop.propertyWithCounter = 20
        assertEquals(prop.propertyWithCounter, 20)
        assertEquals(prop.counter, 2)
    }

    @Test fun testSetter2() {
        val prop1 = PropertyExample()
        val prop2 = PropertyExample()
        
        prop1.propertyWithCounter = 10
        prop2.propertyWithCounter = 20
        assertNotNull(prop1.propertyWithCounter)
        assertNotNull(prop2.propertyWithCounter)
        assertEquals(prop1.propertyWithCounter, 10)
        assertEquals(prop2.propertyWithCounter, 20)
        assertEquals(prop1.counter, 1)
        assertEquals(prop2.counter, 1)
    }
}
