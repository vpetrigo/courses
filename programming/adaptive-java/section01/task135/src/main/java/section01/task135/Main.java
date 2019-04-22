package section01.task135;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        int[] x = new int[]{0, 0};

        while (n-- > 0) {
            List<String> tokens =
                    Arrays.asList(reader.readLine().split("\\s+"));
            int movement = Integer.parseInt(tokens.get(1));

            switch (tokens.get(0)) {
                case "North":
                    x[1] += movement;
                    break;
                case "West":
                    x[0] -= movement;
                    break;
                case "East":
                    x[0] += movement;
                    break;
                case "South":
                    x[1] -= movement;
                    break;
                default:
                    break;
            }
        }

        System.out.printf("%d %d\n", x[0], x[1]);
    }
}
