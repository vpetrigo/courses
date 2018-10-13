package section03.task76;

public class GiftBox<T> implements Box<T> {
    private T gift;

    @Override
    public void put(T item) {
        System.out.println("Put gift");
        gift = item;
    }

    @Override
    public T get() {
        return gift;
    }
}
