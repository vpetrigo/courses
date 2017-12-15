import java.util.Objects;

/**
 * Pair
 */
public class Pair<K, V> {
    private K key;
    private V value;

    private Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }

    static public <K, V> Pair<K, V> of(K key, V value) {
        return new Pair<>(key, value);
    }

    public K getFirst() {
        return key;
    }

    public V getSecond() {
        return value;
    }

    public boolean equals(Pair pair) {
        return Objects.equals(pair.key, key) && Objects.equals(pair.value, value);
    }

    public int hashCode() {
        return Objects.hashCode(this.key) + Objects.hashCode(this.value);
    }
}