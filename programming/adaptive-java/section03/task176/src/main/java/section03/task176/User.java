package section03.task176;

import java.util.Objects;
import org.jetbrains.annotations.Nullable;

public class User {
    private String login;
    @Nullable
    private Account account;

    public User(String login, @Nullable Account account) {
        this.login = login;
        this.account = account;
    }

    public String getLogin() {
        return login;
    }

    @Nullable
    public Account getAccount() {
        return account;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }

        User user = (User) o;
        return Objects.equals(login, user.login) && Objects
                .equals(account, user.account);
    }

    @Override
    public int hashCode() {
        return Objects.hash(login, account);
    }

    @Override
    public String toString() {
        return "User{" + "login='" + login + '\'' + ", account=" + account + '}';
    }
}
