package Program1;

import java.util.Scanner;

public class ComplexNumber {
    static Scanner stdin = new Scanner(System.in);
    double re, im;
    public ComplexNumber(double real, double imag) {
        re = real;
        im = imag;
    }
    public ComplexNumber() {
        this(0.0, 0.0);
    }
    public ComplexNumber add(ComplexNumber other) {
        return new ComplexNumber(this.re + other.re, this.im + other.im);
    }
    public ComplexNumber subtract(ComplexNumber other) {
        return new ComplexNumber(this.re - other.re, this.im - other.im);
    }
    public String toString() {
        return String.valueOf(re) + " + " + String.valueOf(im) + " i";
    }
    public void display() {
        System.out.println(toString());
    }
    public static ComplexNumber readComplexNumber() {
        Scanner in = stdin;
        double re = in.nextDouble();
        if (!in.next().equals("+")) {
            return new ComplexNumber();
        }
        double im = in.nextDouble();
        if (!in.next("i").equals("i")) {
            System.out.println("Bad input!!");
            return new ComplexNumber();
        }
        return new ComplexNumber(re, im);
    }
    public static void main(String[] args) {
        Scanner in = stdin;
        while(true) {
            System.out.println("0. Exit  1. Add  2. Subtract");
            int choice = in.nextInt();
            switch (choice) {
                case 0:
                    System.exit(0);
                case 1:
                    System.out.print("Enter complex number 1: ");
                    ComplexNumber a = readComplexNumber();
                    System.out.print("Enter complex number 2: ");
                    ComplexNumber b = readComplexNumber();
                    a.add(b).display();
                    break;
                case 2:
                    System.out.print("Enter complex number 1: ");
                    ComplexNumber x = readComplexNumber();
                    System.out.print("Enter complex number 2: ");
                    ComplexNumber y = readComplexNumber();
                    x.subtract(y).display();
                    break;
                default:
                    System.out.println("Invalid Option!!");
            }
        }
    }
}
