package section03.task59;

import java.util.Calendar;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class UserActivityMonitoring {
    public static void main(String[] args) {
        LogEntry log1 = new LogEntry(new Calendar.Builder()
                .setDate(2016, 1, 1).build().getTime(), "A", "https://example.org");
        LogEntry log2 = new LogEntry(new Calendar.Builder()
                .setDate(2016, 1, 1).build().getTime(), "B", "https://example.org/?q=");
        LogEntry log3 = new LogEntry(new Calendar.Builder()
                .setDate(2016, 1, 1).build().getTime(), "C", "https://example.org");
        List<LogEntry> logs = List.of(log1, log2, log3);
        Map<String, Long> clickCounts = logs.stream()
                .collect(Collectors.groupingBy(LogEntry::getUrl, Collectors.counting()));

        clickCounts.forEach((k, v) -> System.out.printf("URL: %s - clicks: %d\n", k, v));
    }
}
