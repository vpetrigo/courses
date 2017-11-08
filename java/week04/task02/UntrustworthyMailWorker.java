public class UntrustworthyMailWorker implements MailService {
    private RealMailService realMailService;
    private MailService[] thirdParties;

    public UntrustworthyMailWorker(MailService[] thirdParties) {
        this.thirdParties = thirdParties.clone();
        this.realMailService = new RealMailService();
    }

    public RealMailService getRealMailService() {
        return realMailService;
    }

    @Override
    public Sendable processMail(Sendable mail) {
        for (MailService ms : thirdParties) {
            mail = ms.processMail(mail);
        }

        return realMailService.processMail(mail);
    }
}