public class IntegralLeftTriangle {
    public static double integrate(DoubleUnaryOperator f, double a, double b) {
        double result = 0;
        for (; a < b; a += Math.pow(10, -6)) {
            result += f.applyAsDouble(a)*Math.pow(10, -6);
        }
        return result;
    }
}
