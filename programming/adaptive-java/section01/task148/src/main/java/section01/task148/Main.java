package section01.task148;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.stream.IntStream;

public class Main {
    static private int getNumberOfIntegersWithSameDigitSum(int number) {
        int originDigitsSum = getDigitsSum(number);

        return (int) IntStream.range(0, number)
                              .filter(value -> getDigitsSum(value) ==
                                               originDigitsSum).count();
    }

    static private int getDigitsSum(int number) {
        int sum = 0;

        while (number > 0) {
            sum += number % 10;
            number /= 10;
        }

        return sum;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));
        int num = Integer.parseInt(reader.readLine());

        System.out.println(getNumberOfIntegersWithSameDigitSum(num));
    }
}
