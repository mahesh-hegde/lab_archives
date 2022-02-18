package Prelims;

import java.util.Scanner;

public class FindIn2DArray {
    public static void find_num(int[][] array, int rows, int cols, int search) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (array[i][j] == search) {
                    System.out.printf("Found at row %d, column %d\n", i+1, j+1);
                    return;
                }
            }
        }
        System.out.println("Not found");
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter rows and columns: ");
        int rows = in.nextInt();
        int cols = in.nextInt();
        int[][] array = new int[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                array[i][j] = (int)(Math.random() * 200);
                // some random number between 0..199
                System.out.printf("%3d ", array[i][j]);
            }
            System.out.println();
        }
        while(true) {
            System.out.print("0 to Exit or 1 Search for a number: ");
            int choice = in.nextInt();
            switch(choice) {
                case 0:
                    System.exit(0);
                case 1:
                    System.out.print("Enter number to search: ");
                    int search = in.nextInt();
                    find_num(array, rows, cols, search);
                    break;
                default:
                    System.out.println("Invalid Option!!");
            }
        }
    }
}
