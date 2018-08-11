package section01.task154;

import java.util.Scanner;

public class RomanNumbers {
    private final static int[] numberValues = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1}; // array containing all of the values
    private final static String[] numberLetters = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"}; // array containing all of the numerals

    static int toNumeric(String romanNumber) {
        for (int i = 0; i < numberLetters.length; ++i) {
            if (romanNumber.startsWith(numberLetters[i])) {
                return numberValues[i] + toNumeric(romanNumber.replaceFirst(numberLetters[i], ""));
            }
        }

        return 0;
    }

    static public void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        String romanNumber = reader.nextLine();

        System.out.println(toNumeric(romanNumber));
    }
}
