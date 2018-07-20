package section03.task54;

import java.util.List;

/**
 * Account: number: String, balance: Long, transactions: List<Transaction>
 */
public class Account {
    private String number;
    private Long balance;
    private List<Transaction> transactions;

    public Account(String accName, Long accBalance, List<Transaction> accTransactions) {
        number = accName;
        balance = accBalance;
        transactions = accTransactions;
    }

    public String getNumber() {
        return number;
    }

    public void setNumber(String number) {
        this.number = number;
    }

    public Long getBalance() {
        return balance;
    }

    public void setBalance(Long balance) {
        this.balance = balance;
    }

    public List<Transaction> getTransactions() {
        return transactions;
    }

    public void setTransactions(List<Transaction> transactions) {
        this.transactions = transactions;
    }
}
