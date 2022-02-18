package Program8;

import java.util.Scanner;
import java.util.function.Predicate;

public class LambdaFunctions {
    public static boolean isPrime(int n) {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }
    public static boolean isPalindrome(int n) {
        int n2 = n;
        int reverse = 0;
        while (n2 != 0) {
            reverse = (reverse * 10) + (n2 % 10);
            n2 = n2 / 10;
        }
        return reverse == n;
    }
    public static Predicate<Integer> operation(int n) {
        switch (n) {
            case 1:
                return (Integer m) -> m % 2 == 1;
            case 2:
                return LambdaFunctions::isPrime;
            case 3:
                return LambdaFunctions::isPalindrome;
            default:
                throw new IllegalArgumentException("Invalid Number " + n);
        }
    }
    public static void main(String[] args) {
        String[] funcs = {"", "isOdd", "isPrime", "isPalindrome"};
        Scanner in = new Scanner(System.in);
        while (true) {
            System.out.print("Number: ");
            int num = in.nextInt();
            System.out.print("Operation (0. Exit 1. isOdd 2. isPrime 3. isPalindrome): ");
            int op = in.nextInt();
            if (op == 0) {
                System.exit(0);
            }
            Predicate<Integer> predicate = operation(op);
            System.out.printf("%s(%d) == %b\n\n", funcs[op], num, predicate.test(num));
        }
    }
}
