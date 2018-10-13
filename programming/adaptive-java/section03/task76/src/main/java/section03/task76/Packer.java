package section03.task76;

/**
 This packer has too much freedom and could repackage stuff in wrong direction.
 Fix method types in signature and add implementation.
 */
public class Packer {
    public void repackage(Box<? super Bakery> to, Box<? extends Bakery> from) {
        // Implement repackaging
        to.put(from.get());
    }
}
