package section03.task176;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.Optional;

public class ShopTest {
    @Test
    void testFindUserByLogin() {
        User user1 = new User("Vasya", new Account("123", 0));
        User user2 = new User("Petya", new Account("234", 100));
        Shop.addUser(user1);
        Shop.addUser(user2);

        Optional<User> foundUser1 = Shop.findUserByLogin("Vasya");

        Assertions.assertTrue(foundUser1.isPresent());
        Assertions.assertEquals(user1, foundUser1.orElseGet(() -> new User(""
                , new Account("", 0))));

        Optional<User> foundUser2 = Shop.findUserByLogin("Petya");

        Assertions.assertTrue(foundUser2.isPresent());
        Assertions.assertEquals(user2, foundUser2.orElseGet(() -> new User(""
                , new Account("", 0))));
    }

    @AfterEach
    void tearDown() {
        Shop.resetUsers();
    }
}
