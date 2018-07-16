package section01.task164;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class QueenChessChecker {
    public static boolean queenHitChecker(int x1, int y1, int x2, int y2) {
        return (x1 == x2) || (y1 == y2) || (Math.abs(x1 - x2) == Math.abs(y1 - y2));
    }

    public static void main(String[] args) throws IOException {
        System.out.println(QueenChessChecker.class.getName());
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        List<Integer> coords = Arrays.stream(reader.readLine().split("\\s"))
                .map(Integer::parseInt).collect(Collectors.toList());

        System.out.println(queenHitChecker(coords.get(0), coords.get(1),
                coords.get(2), coords.get(3)) ? "YES" : "NO");
    }
}
