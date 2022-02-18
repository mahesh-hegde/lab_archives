package Prelims;

import java.util.Scanner;

public class SecondsConverter {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Seconds: ");
        int total = in.nextInt();
        int seconds = total % 60;
        int minutes = (total / 60) % 60;
        int hours = total / 3600;
        System.out.printf("%02d:%02d:%02d", hours, minutes, seconds);
    }
}
