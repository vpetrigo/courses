import java.lang.IllegalArgumentException;

public class SquareRoot {
    public static double sqrt(double x) {
        if (x < 0) {
            throw new IllegalArgumentException("Expected non-negative number, got " + x);
        }

        return Math.sqrt(x);
    }

    public static void main(String[] args) {
        try {
            sqrt(-2);
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}