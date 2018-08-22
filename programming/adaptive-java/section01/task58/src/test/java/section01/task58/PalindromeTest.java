package section01.task58;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;

public class PalindromeTest {
    @Test
    void testPalindrome() {
        String palindrome = "kayak";
        Assertions.assertTrue(Palindrome.isPalindrome(palindrome));
    }

    @Test
    void testNonPalindrome() {
        String palindrome = "kayaka";
        Assertions.assertFalse(Palindrome.isPalindrome(palindrome));
    }
}
