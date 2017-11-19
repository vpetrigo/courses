public class Thief implements MailService {
    private int minCost;
    private int stolenCost;

    public Thief(int minCost) {
        this.minCost = minCost;
    }

    public int getStolenValue() {
        return stolenCost;
    }

    @Override
    public Sendable processMail(Sendable mail) {
        if (mail instanceof MailPackage) {
            MailPackage pack = (MailPackage) mail;
            int packCost = pack.getContent().getPrice();
            if (packCost >= minCost) {
                stolenCost += packCost;
                Package empty = new Package("stones instead of " + pack.getContent().getContent(), 0);
                return new MailPackage(pack.getFrom(), pack.getTo(), empty);
            }
        }

        return mail;
    }
}