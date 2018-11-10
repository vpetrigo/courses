package section03.task88;

public class ReflexiveBaker {
    /**
     * Create bakery of the provided class.
     *
     * @param order class of bakery to create
     * @return bakery object
     */
    public <T extends Bakery> T bake(Class<T> order) {
        // Add implementation here
        try {
            return order.getConstructor().newInstance();
        }
        catch (Exception e) {
            return null;
        }
    }
}
