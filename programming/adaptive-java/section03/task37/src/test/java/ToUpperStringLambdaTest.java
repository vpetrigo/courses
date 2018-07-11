package section03.task37;

import static section03.task37.ToUpperStringLambda.processString;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class ToUpperStringLambdaTest {
    @Test
    public void testSevenArgsLambda() {
        String test = new String("The lambda has too many string arguments.");
        String expected = new String("THELAMBDAHASTOOMANYSTRINGARGUMENTS.");
        assertEquals(expected, processString(test, (a, b, c, d, e, f, g) -> new StringBuilder().append(a.toUpperCase())
                                                                                                .append(b.toUpperCase())
                                                                                                .append(c.toUpperCase())
                                                                                                .append(d.toUpperCase())
                                                                                                .append(e.toUpperCase())
                                                                                                .append(f.toUpperCase())
                                                                                                .append(g.toUpperCase())
                                                                                                .toString()));
    }
}