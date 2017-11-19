public class Inspector implements MailService {
    public static final String WEAPONS = "weapons";
    public static final String BANNED_SUBSTANCE = "banned substance";

    @Override
    public Sendable processMail(Sendable mail) {
        if (mail instanceof MailPackage) {
            MailPackage mpack = (MailPackage) mail;
            Package pack = mpack.getContent();
            String content = pack.getContent();

            if (content.contains(WEAPONS) ||
                content.contains(BANNED_SUBSTANCE)) {
                    throw new IllegalPackageException();
            }
            
            if (content.contains("stones")) {
                throw new StolenPackageException();
            }
        }

        return mail;
    }
}