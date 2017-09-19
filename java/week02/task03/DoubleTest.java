public class DoubleTest {
    public static boolean doubleExpression(double a,
            double b, double c) {
        final double accuracy = 1e-4;

        return Math.abs(c - (a + b)) < accuracy;
    }

    public static void main(String[] args) {
        assert doubleExpression(0.1, 0.2, 0.3);
    }
}
