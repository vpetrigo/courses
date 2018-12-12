package section01.task194;

import java.util.Scanner;

class Main2 {
    static void printSplit(int[] arr, int l) {
        for (int i = 0; i < l; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }

    static int next(int[] arr, int l) {
        int i = l - 1;
        int sum = 0;

        do {
            sum += arr[i--];
        } while (i > 0 && arr[i - 1] <= arr[i]);

        arr[i]++;
        l = i + sum;

        for (int j = i + 1; j < l; j++) {
            arr[j] = 1;
        }

        return l;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int l = n;
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = 1;
        }

        printSplit(arr, n);
        do {
            l = next(arr, l);
            printSplit(arr, l);
        } while (l > 1);
    }
}