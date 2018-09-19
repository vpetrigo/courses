package section03.task170;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;

import java.util.Arrays;
import java.util.List;

public class AccountFilterTest {
    @Test
    void testNonEmptyAccountsFiltering() {
        List<Account> accounts = Arrays
                .asList(new Account("123", 0L, false),
                        new Account("234", 1L, false),
                        new Account("456", 0L, false),
                        new Account("567", 1L, false));
        List<Account> nonEmptyAccounts = Filtering.filter(accounts,
                (account -> account.getBalance() > 0));
        List<Account> expected = Arrays
                .asList(new Account("234", 1L, false),
                        new Account("567", 1L, false));

        Assertions.assertEquals(expected, nonEmptyAccounts);
    }

    @Test
    void testRichAndNonLockedAccounts() {
        List<Account> accounts1 = Arrays
                .asList(new Account("123", 100_000_000L, false),
                        new Account("234", 1L, false),
                        new Account("456", 0L, false),
                        new Account("567", 100_000_000L, false));
        List<Account> accountsWithTooMuchMoney = Filtering.filter(accounts1,
                (account -> !account.isLocked() && account.getBalance() >= 100_000_000L));
        List<Account> expected = Arrays
                .asList(new Account("123", 100_000_000L, false),
                        new Account("567", 100_000_000L, false));
        Assertions.assertEquals(expected, accountsWithTooMuchMoney);

        List<Account> accounts2 = Arrays
                .asList(new Account("123", 100_000_000L, true),
                        new Account("234", 1L, false),
                        new Account("456", 0L, false),
                        new Account("567", 100_000_000L, false));
        List<Account> accountsWithTooMuchMoney2 = Filtering.filter(accounts2,
                (account -> !account.isLocked() && account.getBalance() >= 100_000_000L));
        List<Account> expected2 = Arrays
                .asList(new Account("567", 100_000_000L, false));
        Assertions.assertEquals(expected2, accountsWithTooMuchMoney2);
    }
}
