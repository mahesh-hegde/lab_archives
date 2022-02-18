package Prelims;

import java.util.Scanner;

public class Staircase {
    static final String pattern = "$";
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter n: ");
        int n = in.nextInt();
        for (int i = 0; true; i++) {
            for (int j = 0; j < i; j++) {
                System.out.print(pattern);
                n--;
                if (n == 0) break;
            }
            System.out.println();
            if (n == 0) break;
        }
    }
}
