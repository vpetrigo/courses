package section03.task58;

public class Account {
    private String name;
    private Long balance;

    public Account(String accName, Long accBalance) {
        name = accName;
        balance = accBalance;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Long getBalance() {
        return balance;
    }

    public void setBalance(Long balance) {
        this.balance = balance;
    }
}
