package section01.task71;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Replace {
    public static String spaceReplace(String input) {
        return input.replaceAll("\\s+", "_");
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));
        String toReplace = reader.readLine();
        System.out.println(spaceReplace(toReplace));
    }
}
