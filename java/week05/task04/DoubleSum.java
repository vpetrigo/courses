import java.util.Scanner;

public class DoubleSum {
    public static void main(String[] args) {
        Scanner double_scanner = new Scanner(System.in);
        double sum = 0;

        while (double_scanner.hasNext()) {
            if (double_scanner.hasNextDouble())
            {
                sum += double_scanner.nextDouble();
            }
            else
            {
                double_scanner.next();
            }
        }

        System.out.printf("%.6f", sum);
    }
}