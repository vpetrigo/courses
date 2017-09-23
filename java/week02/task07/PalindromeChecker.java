public class PalindromeChecker {
    /**
     * Checks if given <code>text</code> is a palindrome.
     *
     * @param text any string
     * @return <code>true</code> when <code>text</code>ais a palindrome, <code>false</code> otherwise
     */
    public static boolean isPalindrome(String text) {
        String orig = text.replaceAll("[^a-zA-Z0-9]", "");
        String rev = new StringBuilder(orig).reverse().toString();
        return orig.equalsIgnoreCase(rev); // your implementation here
    }

    public static void test() {
        assert isPalindrome("ababa");
        assert isPalindrome("Madam, I'm Adam");
        assert !isPalindrome("abaca");
    }

    public static void main(String[] args) {
        test();
    }
}
