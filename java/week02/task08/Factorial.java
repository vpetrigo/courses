public class Factorial {
    /**
     * Calculates factorial of given <code>value</code>.
     *
     * @param value positive number
     * @return factorial of <code>value</code>
     */
    public static BigInteger factorial(int value) {
        BigInteger result = BigInteger.valueOf(1);

        for (long i = 2; i < value + 1; ++i) {
            result = result.multiply(BigInteger.valueOf(i));
        }

        return result;
    }

    public static BigInteger factorial_rec(int value) {
        return value > 0 ? BigInteger.valueOf(value).multiply(factorial_rec(value - 1)) : BigInteger.ONE;
    }

    public static void test() {
        assert factorial(2).equals(BigInteger.valueOf(2));
        assert factorial(3).equals(BigInteger.valueOf(6));
        assert factorial(4).equals(BigInteger.valueOf(24));
        assert factorial_rec(2).equals(BigInteger.valueOf(2));
        assert factorial_rec(3).equals(BigInteger.valueOf(6));
        assert factorial_rec(4).equals(BigInteger.valueOf(24));
    }

    public static void main(String[] args) {
        test();
        benchmark();
    }
}
