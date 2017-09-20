public class FlipBit {
    /**
	 * Flips one bit of the given <code>value</code>.
	 *
	 * @param value     any number
	 * @param bitIndex  index of the bit to flip, 1 <= bitIndex <= 32
	 * @return new value with one bit flipped
	 */
	public static int flipBit(int value, int bitIndex) {
		return value ^ (1 << bitIndex - 1); 
	}

	public static void main(String[] args) {
		assert flipBit(0, 1) == 1;
		assert flipBit(5, 7) == 69;
	}
}
