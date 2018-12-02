package section01.task94;

public class Kadane {
    private long maxSum;
    private long maxStart;
    private long maxEnd;

    private Kadane(long maxSum, long maxStart, long maxEnd) {
        this.maxSum = maxSum;
        this.maxStart = maxStart;
        this.maxEnd = maxEnd;
    }

    public static Kadane getSubArrayMaxSum(int[] arr) {
        int max = arr[0];
        int maxStart = 0;
        int maxEnd = 0;
        int currentStart = 0;
        int maxEndingHere = max;

        for (int i = 1; i < arr.length; ++i) {
            if (maxEndingHere + arr[i] < arr[i]) {
                maxEndingHere = arr[i];
                currentStart = i;
            }
            else
            {
                maxEndingHere += arr[i];
            }

            if (max < maxEndingHere) {
                maxStart = currentStart;
                maxEnd = i;
                max = maxEndingHere;
            }
        }

        return new Kadane(max, maxStart, maxEnd);
    }

    public long getMaxSum() {
        return maxSum;
    }

    public long getMaxStart() {
        return maxStart;
    }

    public long getMaxEnd() {
        return maxEnd;
    }
}
