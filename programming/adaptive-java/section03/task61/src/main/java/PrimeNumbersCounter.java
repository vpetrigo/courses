package section03.task61;

import java.util.stream.LongStream;

class NumberUtils {
    public static boolean isPrime(long num) {
        return LongStream.rangeClosed(2, (long)Math.sqrt(num)).allMatch(value -> num % value != 0);
    }
}

public class PrimeNumbersCounter {
    public static LongStream createPrimesFilteringStream(long rangeBegin, long rangeEnd) {
        return LongStream.rangeClosed(rangeBegin, rangeEnd).filter(NumberUtils::isPrime).parallel();
    }

    public static void main(String[] args) {
        System.out.println(NumberUtils.isPrime(2));
        System.out.println(NumberUtils.isPrime(4));
    }
}
