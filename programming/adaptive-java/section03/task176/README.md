There are two related tasks with a common domain model:

```kotlin
Account (guid: UUID, balance: long)
User (login: String, account: Account)
```

Both classes have getters for all corresponding fields: `getGuid()`,
`getBalance()`, `getLogin()`, `getAccount()`.

You need to write two method for processing domain objects.

## Task 1

You need to write a method `findUserByLogin(String login)` that returns
an optional value of type `Optional<User>`. If the user exists in the users
set you need to return non-empty optional wrapping the user inside, otherwise
returned optional should be empty.

**Important.** Use the provided template for your solution. Do not change it!

## Task 2

Using the method you wrote for finding an user by their login, write a new
method `printBalanceIfNotEmpty(String userLogin)` that prints an account 
balance for an existing user if `balance > 0`. In this case, the result format
should print the string:

```
<login>: <balance>
```

If the user is not found, account is `null` or the `balance = 0`, then the
method should not print anything.

Do not forget to use optional for avoiding NPE.
