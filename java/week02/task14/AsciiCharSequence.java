import java.util.Arrays;

public class AsciiCharSequence implements CharSequence {
    private byte[] symbols;

    public AsciiCharSequence(byte[] symbols) {
        this.symbols = Arrays.copyOf(symbols, symbols.length);
    }

    @Override
    public char charAt(int index) {
        if (index < 0 || index > symbols.length - 1) {
            throw new IndexOutOfBoundsException();
        }
        return (char) symbols[index];
    }

    @Override
    public int length() {
        return symbols.length;
    }

    @Override
    public AsciiCharSequence subSequence(int start, int end) {
        return new AsciiCharSequence(Arrays.copyOfRange(symbols, start, end));
    }

    @Override
    public String toString() {
        return new String(symbols);
    }
}
