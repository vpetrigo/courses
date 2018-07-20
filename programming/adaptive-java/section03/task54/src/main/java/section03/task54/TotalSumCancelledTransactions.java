package section03.task54;

import java.util.Calendar;
import java.util.List;

public class TotalSumCancelledTransactions {
    /**
     * Calculates the general sum of canceled transactions for all non empty accounts in the list
     */
    public static long calcSumOfCanceledTransOnNonEmptyAccounts(List<Account> accounts) {
        return accounts.stream().filter(acc -> acc.getBalance() > 0).flatMap(acc -> acc.getTransactions().stream())
                .filter(tr -> tr.getState() == Transaction.State.CANCELED).mapToLong(Transaction::getSum).sum();
    }

    public static void main(String[] args) {
        Transaction tr1 = new Transaction("123", Transaction.State.CANCELED,
                100L, new Calendar.Builder().setDate(2017, 1, 1)
                .build().getTime());
        Transaction tr2 = new Transaction("124", Transaction.State.PROCESSING,
                200L, new Calendar.Builder().setDate(2017, 1, 21)
                .build().getTime());
        Transaction tr3 = new Transaction("126", Transaction.State.CANCELED,
                400L, new Calendar.Builder().setDate(2017, 5, 21)
                .build().getTime());

        Account account1 = new Account("1000", 1000L, List.of(tr2));
        Account account2 = new Account("1001", 2000L, List.of(tr3));
        Account account3 = new Account("1000", 0L, List.of(tr1));

        System.out.println(calcSumOfCanceledTransOnNonEmptyAccounts(List.of(account1, account2, account3)));
    }
}
