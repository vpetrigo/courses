package section01.task38;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.List;

public class GradeCounterTest {
    @Test public void testGradeDistCalculation1() {
        List<Integer> grades = List.of(2, 3, 4, 5);

        Assertions.assertArrayEquals(new int[] {1, 1, 1, 1},
                GradeCounter.calculateGradesDistribution(grades));
    }

    @Test public void testGradeDistCalculation2() {
        List<Integer> grades = List.of(2, 2, 2, 2);

        Assertions.assertArrayEquals(new int[] {4, 0, 0, 0},
                GradeCounter.calculateGradesDistribution(grades));
    }
}
