package Prelims;

import java.util.Scanner;

public class SumCombinations {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter n: ");
        int count = 0;
        int n = in.nextInt();
        for (int i = 0; i <= 9999; i++) {
            int w = i / 1000; // MSB
            int x = (i / 100) % 10;
            int y = (i / 10) % 10;
            int z = (i % 10);
            if (w+x+y+z == n) {
                count++;
                // System.out.printf("%d + %d + %d + %d\n", w, x, y, z);
            }
        }
        System.out.println("Count = " + count);
    }
}
