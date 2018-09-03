package section01.task84;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class FrequencyCounter {
    public static <T extends Number> boolean hasMajority(List<T> numList) {
        int confidence = 0;
        T candidate = null;

        for (T elem : numList) {
            if (confidence == 0) {
                candidate = elem;
                ++confidence;
            } else if (candidate.equals(elem)) {
                ++confidence;
            } else {
                --confidence;
            }
        }

        int count = 0;

        for (T elem : numList) {
            count += (elem.equals(candidate)) ? 1 : 0;
        }

        return count > numList.size() / 2;
    }

    public static void main(String[] args) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            reader.readLine();
            List<Integer> numList = Arrays.stream(reader.readLine().split("\\s+"))
                    .map(Integer::parseInt).collect(Collectors.toList());
            System.out.println(hasMajority(numList) ? 1 : 0);
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}
