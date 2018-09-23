package section03.task176;

import java.util.HashSet;
import java.util.Objects;
import java.util.Optional;
import java.util.Set;

public class Shop {
    private static final Set<User> users = new HashSet<>();

    public static Optional<User> findUserByLogin(String login) {
        return users.stream().filter(user -> Objects.equals(user.getLogin(),
                login)).findFirst();
    }

    public static boolean addUser(User user) {
        return users.add(user);
    }

    public static void resetUsers() {
        users.clear();
    }
}
