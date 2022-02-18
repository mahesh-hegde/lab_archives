package Prelims;

import java.util.Scanner;

public class TwoSameDigit {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter 3 numbers: ");
        int a = in.nextInt() % 10;
        int b = in.nextInt() % 10;
        int c = in.nextInt() % 10;
        System.out.println(a == b || b == c || a == c);
    }
}
