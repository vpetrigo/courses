package section01.task58;

import java.util.Scanner;
import java.util.stream.IntStream;

public class Palindrome {
    static public boolean isPalindrome(String string) {
        return IntStream.range(0, string.length() / 2).allMatch(i -> string.charAt(i) == string.charAt(string.length() - i - 1));
    }

    static public void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        System.out.println(isPalindrome(reader.nextLine()) ? "yes" : "no");
    }
}
