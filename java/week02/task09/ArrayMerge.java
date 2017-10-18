public class ArrayMerge {
    /**
     * Merges two given sorted arrays into one
     *
     * @param a1 first sorted array
     * @param a2 second sorted array
     * @return new array containing all elements from a1 and a2, sorted
     */
    public static int[] mergeArrays(int[] a1, int[] a2) {
        int i = 0;
        int j = 0;
        int res[] = new int[a1.length + a2.length];

        while (i != a1.length && j != a2.length) {
            res[i + j] = (a1[i] < a2[j]) ? a1[i++] : a2[j++];
        }

        while (i != a1.length) {
            res[i + j] = a1[i++];
        }

        while (j != a2.length) {
            res[i + j] = a2[j++];
        }

        return res; // your implementation here
    }

    public static void test() {
        assert Arrays.equals(mergeArrays(new int[] {
            0,
            2,
            2
        }, new int[] {
            1,
            3
        }), new int[] {
            0,
            1,
            2,
            2,
            3
        });
    }

    public static void main(String[] args) {
        test();
    }
}
