public class IntegerChecker {
    /**
     * Checks if given <code>value</code> is a power of two.
     *
     * @param value any number
     * @return <code>true</code> when <code>value</code> is power of two, <code>false</code> otherwise
     */
    public static boolean isPowerOfTwo(int value) {
        return (value != 0) && (Math.abs(value) & (Math.abs(value) - 1)) == 0;
    }

    public static void test() {
        assert isPowerOfTwo(2);
        assert !isPowerOfTwo(3);
        assert isPowerOfTwo(32);
        assert !isPowerOfTwo(92);
    }

    public static void main(String[] args) {
        test();
    }
}