import java.util.stream.IntStream;

public class PseudoRandomStream {
    public static void main(String[] args) {
        int[] arr = pseudoRandomStream(13).limit(10).toArray();

        for (int e : arr)
        {
            System.out.println(e);
        }
    }

    public static IntStream pseudoRandomStream(int seed) {
        return IntStream.iterate(seed, n -> n * n / 10 % 1000); // your implementation here
    }
}