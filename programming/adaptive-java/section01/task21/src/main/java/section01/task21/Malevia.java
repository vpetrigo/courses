package section01.task21;

import java.util.*;
import java.util.function.Function;

public class Malevia {
    public static void main(String[] args) {
        Map<String, Function<List<Double>, Double>> funMap = new HashMap<>();
        Scanner reader = new Scanner(System.in);
        List<Double> funArgs = new ArrayList<>();
        String roomType = reader.nextLine();

        funMap.put("triangle", (vals) -> { Double p = (vals.get(0) + vals.get(1) + vals.get(2)) / 2;
            return Math.sqrt(p * (p - vals.get(0)) * (p - vals.get(1)) * (p - vals.get(2)));
        });
        funMap.put("rectangle", (vals) -> vals.get(0) * vals.get(1));
        funMap.put("circle", (vals) -> 3.14 * vals.get(0) * vals.get(0));

        while (reader.hasNextDouble())
        {
            funArgs.add(reader.nextDouble());
        }

        System.out.println(funMap.get(roomType).apply(funArgs));
    }
}
