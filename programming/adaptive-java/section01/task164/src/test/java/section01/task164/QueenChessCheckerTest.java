package section01.task164;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class QueenChessCheckerTest {
    @Test void testQueenHit1() {
        int x1 = 1;
        int y1 = 1;
        int x2 = 3;
        int y2 = 3;

        Assertions.assertTrue(QueenChessChecker.queenHitChecker(x1, y1, x2, y2));
    }

    @Test void testQueenHit2() {
        int x1 = 1;
        int y1 = 1;
        int x2 = 4;
        int y2 = 3;

        Assertions.assertFalse(QueenChessChecker.queenHitChecker(x1, y1, x2, y2));
    }

    @Test void testQueenHit3() {
        int x1 = 2;
        int y1 = 2;
        int x2 = 5;
        int y2 = 2;

        Assertions.assertTrue(QueenChessChecker.queenHitChecker(x1, y1, x2, y2));
    }
}
