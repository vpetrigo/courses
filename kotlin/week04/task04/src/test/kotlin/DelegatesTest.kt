package week04.task04

import org.junit.Assert
import org.junit.Test
import properties.delegates_how_it_works.MyDate

class TestDelegatesHowItWorks {
    @Test fun testDate() {
        val d = D()
        d.date = MyDate(2014, 1, 13)
        val message = "The methods 'getValue' and 'setValue' are implemented incorrectly"
        Assert.assertTrue(message, 2014 == d.date.year)
        Assert.assertTrue(message, 1 == d.date.month)
        Assert.assertTrue(message, 13 == d.date.dayOfMonth)
    }
}
