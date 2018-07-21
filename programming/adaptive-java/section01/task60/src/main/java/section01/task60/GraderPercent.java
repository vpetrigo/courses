package section01.task60;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;

public class GraderPercent {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        List<String> grades = Arrays.asList(reader.readLine().split("\\s+"));

        System.out.println((double) grades.stream().filter(s -> s.equals("A")).count() / grades.size());
    }
}
