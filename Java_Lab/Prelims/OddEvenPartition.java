package Prelims;

import java.util.Scanner;

public class OddEvenPartition {
    public static void swap(int[] array, int a, int b) {
        int temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }
    public static int nextOddNum(int[] array, int start) {
        for (int i = start; i < array.length; i++) {
            if (array[i] % 2 == 1) {
                return i;
            }
        }
        return -1;
    }
    public static void partition(int[] array) {
        int i = 0;
        int len = array.length;
        // run through array
        // at any even number, swap with next found odd number
        // and change first_even to that position;
        int oddNumAt = 0;
        while (i < len) {
            oddNumAt = Math.max(i, oddNumAt);
            if (array[i] % 2 != 1) {
                int next = nextOddNum(array, oddNumAt + 1);
                if (next == -1) {
                    return;
                }
                swap(array, i, next);
                oddNumAt = next;
            }
            i++;
        }
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.println("Num of elements: ");
        int len = in.nextInt();
        int[] array = new int[len];
        System.out.print("Enter numbers: ");
        for (int i = 0; i < len; i++) {
            array[i] = in.nextInt();
        }
        partition(array);
        System.out.print("[");
        for (int i = 0; i < len; i++) {
            System.out.printf("%d ", array[i]);
        }
        System.out.println("]");
    }
}
