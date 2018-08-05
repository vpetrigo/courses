package section01.task140;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            int n = Integer.parseInt(reader.readLine());
            System.out.println(Arrays.stream(reader.readLine().split("\\s+"))
                    .mapToInt(Integer::parseInt).distinct().count());
        }
        catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
