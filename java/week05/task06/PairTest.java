/**
 * PairTest
 */
public class PairTest {
    public static void main(String[] args) {
        Pair<Integer, String> test = Pair.of(1, "test");
        Pair<Integer, String> test2 = Pair.of(1, "test2");

        System.out.printf("%d %s\n", test.getFirst(), test.getSecond());
        System.out.println(test.equals(test));
        System.out.println(test.equals(test2));
    }
}