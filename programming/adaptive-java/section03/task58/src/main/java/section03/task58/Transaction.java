package section03.task58;

/**
 * Transaction: uuid: String, sum: Long, account: Account
 */
public class Transaction {
    private String uuid;
    private Long sum;
    private Account account;

    public Transaction(String trUuid, Long trSum, Account trAccount) {
        uuid = trUuid;
        sum = trSum;
        account = trAccount;
    }

    public String getUuid() {
        return uuid;
    }

    public void setUuid(String uuid) {
        this.uuid = uuid;
    }

    public Long getSum() {
        return sum;
    }

    public void setSum(Long sum) {
        this.sum = sum;
    }

    public Account getAccount() {
        return account;
    }

    public void setAccount(Account account) {
        this.account = account;
    }
}
