package section03.task170;

import java.util.Objects;

public class Account {
    private String number;
    private Long balance;
    private boolean isLocked;

    public Account(String number, Long balance, boolean isLocked) {
        this.number = number;
        this.balance = balance;
        this.isLocked = isLocked;
    }

    public String getNumber() {
        return number;
    }

    public Long getBalance() {
        return balance;
    }

    public boolean isLocked() {
        return isLocked;
    }

    @Override
    public boolean equals(Object o) {
        if (o == this) {
            return true;
        }

        if (o instanceof Account) {
            Account cmp = (Account) o;

            return cmp.getNumber().equals(getNumber()) &&
                    cmp.getBalance().equals(getBalance()) &&
                    cmp.isLocked() == isLocked();
        }

        return false;
    }

    @Override
    public int hashCode() {
        return Objects.hash(getNumber(), getBalance(), isLocked());
    }
}
