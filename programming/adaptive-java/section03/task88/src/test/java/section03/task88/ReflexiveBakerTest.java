package section03.task88;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class ReflexiveBakerTest {
    private ReflexiveBaker reflexiveBaker;

    @BeforeEach
    void setUp() {
        reflexiveBaker = new ReflexiveBaker();
    }

    @Test
    void testReflexiveBakerWithBakery() {
        Assertions.assertEquals(Bakery.class,
                                reflexiveBaker.bake(Bakery.class).getClass());
    }

    @Test
    void testReflexiveBakerWithCake() {
        Assertions.assertEquals(Cake.class,
                                reflexiveBaker.bake(Cake.class).getClass());
    }
}
