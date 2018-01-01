import java.util.*;
import java.util.function.*;

public class Main {
    public static void main(String[] args) {
        // Random variables
        String randomFrom = "..."; // Некоторая случайная строка. Можете выбрать ее самостоятельно. 
        String randomTo = "...";  // Некоторая случайная строка. Можете выбрать ее самостоятельно.
        int randomSalary = 100;  // Некоторое случайное целое положительное число. Можете выбрать его самостоятельно.

        // Создание списка из трех почтовых сообщений.
        MailMessage firstMessage = new MailMessage(
                "Robert Howard",
                "H.P. Lovecraft",
                "This \"The Shadow over Innsmouth\" story is real masterpiece, Howard!"
        );

        assert firstMessage.getFrom().equals("Robert Howard"): "Wrong firstMessage from address";
        assert firstMessage.getTo().equals("H.P. Lovecraft"): "Wrong firstMessage to address";
        assert firstMessage.getContent().endsWith("Howard!"): "Wrong firstMessage content ending";

        MailMessage secondMessage = new MailMessage(
                "Jonathan Nola",
                "Christopher Nolan",
                "Брат, почему все так хвалят только тебя, когда практически все сценарии написал я. Так не честно!"
        );

        MailMessage thirdMessage = new MailMessage(
                "Stephen Hawking",
                "Christopher Nolan",
                "Я так и не понял Интерстеллар."
        );

        List<MailMessage> messages = Arrays.asList(
                firstMessage, secondMessage, thirdMessage
        );

        // Создание почтового сервиса.
        MailService<String> mailService = new MailService<>();

        // Обработка списка писем почтовым сервисом
        messages.stream().forEachOrdered(mailService);

        // Получение и проверка словаря "почтового ящика",
        //   где по получателю можно получить список сообщений, которые были ему отправлены
        Map<String, List<String>> mailBox = mailService.getMailBox();

        assert mailBox.get("H.P. Lovecraft").equals(
                Arrays.asList(
                        "This \"The Shadow over Innsmouth\" story is real masterpiece, Howard!"
                )
        ): "wrong mailService mailbox content (1)";

        assert mailBox.get("Christopher Nolan").equals(
                Arrays.asList(
                        "Брат, почему все так хвалят только тебя, когда практически все сценарии написал я. Так не честно!",
                        "Я так и не понял Интерстеллар."
                )
        ): "wrong mailService mailbox content (2)";

        assert mailBox.get(randomTo).equals(Collections.<String>emptyList()): "wrong mailService mailbox content (3)";

        // Создание списка из трех зарплат.
        Salary salary1 = new Salary("Facebook", "Mark Zuckerberg", 1);
        Salary salary2 = new Salary("FC Barcelona", "Lionel Messi", Integer.MAX_VALUE);
        Salary salary3 = new Salary(randomFrom, randomTo, randomSalary);

        // Создание почтового сервиса, обрабатывающего зарплаты.
        MailService<Integer> salaryService = new MailService<>();

        // Обработка списка зарплат почтовым сервисом
        Arrays.asList(salary1, salary2, salary3).forEach(salaryService);

        // Получение и проверка словаря "почтового ящика",
        //   где по получателю можно получить список зарплат, которые были ему отправлены.
        Map<String, List<Integer>> salaries = salaryService.getMailBox();
        assert salaries.get(salary1.getTo()).equals(Arrays.asList(1)): "wrong salaries mailbox content (1)";
        assert salaries.get(salary2.getTo()).equals(Arrays.asList(Integer.MAX_VALUE)): "wrong salaries mailbox content (2)";
        assert salaries.get(randomTo).equals(Arrays.asList(randomSalary)): "wrong salaries mailbox content (3)";
    }

    public static interface Sendable<T> {
        public String getFrom();
        public String getTo();
        public T getContent();
    }

    public static class SimpleSend<T> implements Sendable<T> {
        private final String from;
        private final String to;
        private final T content;

        public SimpleSend(String from, String to, T content) {
            this.from = from;
            this.to = to;
            this.content = content;
        }

        @Override
        public String getFrom() {
            return this.from;
        }

        @Override
        public String getTo() {
            return this.to;
        }

        @Override
        public T getContent() {
            return this.content;
        }
    }

    public static class MailMessage extends SimpleSend<String> {
        // implement here
        public MailMessage(String from, String to, String content) {
            super(from, to, content);
        }
    }
    
    public static class Salary extends SimpleSend<Integer> {
        // implement here
        public Salary(String from, String to, Integer content) {
            super(from, to, content);
        }
    }
    
    public static class MailService<T> implements Consumer<Sendable<T>> {
        private final Map<String, List<T>> mails;
        // implement here
        public MailService() {
            this.mails = new HashMap<>() {
                @Override
                public List<T> get(Object key) {
                    if (this.containsKey(key)) {
                        return super.get(key);
                    }
                
                    return Collections.emptyList();
                }
            };
        }

        @Override
        public void accept(Sendable<T> t) {
            List<T> list = mails.get(t.getTo());

            if (list.size() != 0) {
                list.add(t.getContent());
            }
            else {
                List<T> new_list = new LinkedList<T>();
                new_list.add(t.getContent());
                mails.put(t.getTo(), new_list);
            }
        }

        public Map<String, List<T>> getMailBox() {
            return this.mails;
        }
    }
}