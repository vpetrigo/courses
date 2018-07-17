public class Main {
    public static void main(String[] args) {
        TernaryIntPredicate predicate = (a, b, c) -> a != b && b != c && a != c;

        System.out.println(predicate.test(1, 1, 1));
        System.out.println(predicate.test(1, 2, 1));
        System.out.println(predicate.test(1, 2, 3));
    }
}
