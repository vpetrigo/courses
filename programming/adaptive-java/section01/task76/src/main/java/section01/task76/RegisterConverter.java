package section01.task76;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class RegisterConverter {
    public static void main(String[] args) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            char character = (char) reader.read();

            if (Character.UnicodeBlock.BASIC_LATIN == Character.UnicodeBlock.of(character)) {
                System.out.println(Character.isUpperCase(character) ? Character.toLowerCase(character)
                        : Character.toUpperCase(character));
            }
            else {
                System.out.println(character);
            }
        }
        catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
