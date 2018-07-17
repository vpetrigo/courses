package section01.task38;

import org.jetbrains.annotations.NotNull;

import java.util.*;
import java.util.stream.IntStream;

public class GradeCounter {
    public static int[] calculateGradesDistribution(@NotNull List<Integer> grades) {
        int[] gradesDistr = new int[4];
        grades.forEach((elem) -> gradesDistr[elem - 2] += 1);

        return gradesDistr;
    }

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        List<Integer> grades = new ArrayList<>();
        int nGrades = reader.nextInt();

        IntStream.range(0, nGrades).forEach((n) -> grades.add(reader.nextInt()));
        Arrays.stream(calculateGradesDistribution(grades)).forEach((e) -> System.out.printf("%d ", e));
        calculateGradesDistribution(null);
    }
}
