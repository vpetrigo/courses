package section03.task176;

import java.util.Objects;

public class Account {
    private String guid;
    private long balance;

    public Account(String guid, long balance) {
        this.guid = guid;
        this.balance = balance;
    }

    public String getGuid() {
        return guid;
    }

    public long getBalance() {
        return balance;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }

        Account account = (Account) o;
        return balance == account.balance && Objects.equals(guid, account.guid);
    }

    @Override
    public int hashCode() {
        return Objects.hash(guid, balance);
    }

    @Override
    public String toString() {
        return "Account{" + "guid='" + guid + '\'' + ", balance=" + balance + '}';
    }
}
