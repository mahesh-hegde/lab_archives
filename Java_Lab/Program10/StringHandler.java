package Program10;

import java.util.Arrays;
import java.util.Scanner;

public class StringHandler {
    static String penultimate(String sentence) {
        String[] arr = sentence.split("[ ?!./&]+");
        if (arr.length < 2) {
            throw new IllegalArgumentException("Not enough words\n");
        }
        return arr[arr.length - 2];
    }
    static String replaceJavaPython(String sentence) {
        return sentence.replaceAll("[jJ]ava", "[[Java]]")
                .replaceAll("[pP]ython", "[[Python]]")
                .replaceAll("\\[\\[Java\\]\\]", "Python")
                .replaceAll("\\[\\[Python\\]\\]", "Java");
    }
    static void printSubStrings(String sentence) {
        System.out.println("Got: " + Arrays.toString(sentence.split("[ ?,./&]+")));
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.println("1. Find Penultimate: ");
        System.out.print("Sentence: ");
        String sentence = in.nextLine();
        System.out.println("Penultimate: " + penultimate(sentence));

        System.out.println("2. Replace Java And Python ");
        System.out.print("Sentence: ");
        sentence = in.nextLine();
        System.out.println("After replacement: " + replaceJavaPython(sentence));

        System.out.println("3. Split and print array");
        System.out.print("Sentence: ");
        sentence = in.nextLine();
        printSubStrings(sentence);
    }
}
