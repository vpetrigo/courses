package section03.task51;

import java.util.stream.IntStream;
import java.util.stream.LongStream;

public class StreamFactorial {
    public static long factorial(long n) {
        return LongStream.rangeClosed(2, n).reduce(1, Math::multiplyExact);
    }
}
