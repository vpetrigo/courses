package section03.task58;

import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {
        Account acc1 = new Account("Acc1", 1000L);
        Account acc2 = new Account("Acc2", 500L);
        List<Transaction> transactions = List.of(new Transaction("1", 40L, acc1),
                new Transaction("2", 50L, acc1),
                new Transaction("3", 100L, acc2));

        System.out.println(transactions);
        Map<String, Long> totalSumOfTransByEachAccount = transactions.stream()
                .collect(Collectors.groupingBy(s -> s.getAccount().getName(), Collectors.summingLong(Transaction::getSum)));
        System.out.println(totalSumOfTransByEachAccount);
    }
}
