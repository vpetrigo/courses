public class Thieft implements MailService {
    private int minCost;
    private int stolenCost;

    public Thieft(int minCost) {
        this.minCost = minCost;
    }

    public int getStolenValue() {
        return stolenCost;
    }

    @Override
    public Sendable processMail(Sendable mail) {
        if (mail instanceof MailPackage) {
            MailPackage pack = (MailPackage) mail;

            if (pack.getContent().getPrice() >= minCost) {
                Package empty = new Package("stones instead of " + pack.getContent().getContent(), 0);
                return new MailPackage(pack.getFrom(), pack.getTo(), empty);
            }
        }

        return mail;
    }
}