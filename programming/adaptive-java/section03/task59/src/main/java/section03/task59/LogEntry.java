package section03.task59;

import java.util.Date;

public class LogEntry {
    private final Date created;
    private final String login;
    private final String url;

    public LogEntry(Date created, String login, String url) {
        this.created = created;
        this.login = login;
        this.url = url;
    }

    public Date getCreated() {
        return created;
    }

    public String getLogin() {
        return login;
    }

    public String getUrl() {
        return url;
    }
}
