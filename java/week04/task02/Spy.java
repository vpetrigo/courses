import java.util.logging.Logger;

public class Spy implements MailService {
    private Logger logger;
    public static final String AUSTIN_POWERS = "Austin Powers";

    public Spy(Logger logger) {
        this.logger = logger;
    }

    @Override
    public Sendable processMail(Sendable mail) {
        if (mail instanceof MailMessage) {
            MailMessage test = (MailMessage) mail;

            if (test.getTo().equals(AUSTIN_POWERS) || test.getFrom().equals(AUSTIN_POWERS)) {
                String warn = String.format("Detected target mail correspondence: from %s to %s \"%s\"",
                                            test.getFrom(), test.getTo(), test.getMessage());
                logger.warning(warn);
            }
            else {
                String info = String.format("Usual correspondence: from %s to %s", 
                                            test.getFrom(), test.getTo());
                logger.info(info);
            }
        }

        return mail;
    }
}