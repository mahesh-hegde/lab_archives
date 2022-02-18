package Program2;

import java.util.Random;
import java.util.Scanner;

public class Prog2 {
    public static void printAll(Object[] array) {
        for (Object i: array) {
            System.out.print(i.toString());
        }
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Num of entries: ");
        int n = in.nextInt();
        var students = new Student[n];
        var colleges = new College[n];
        var employees = new Employee[n];
        for (int i = 0; i < n; i++) {
            System.out.printf("Student[%d] ::\n", i);
            students[i] = Student.readStudent();
            System.out.printf("College[%d] ::\n", i);
            colleges[i] = College.readCollege();
            System.out.printf("Employee[%d] ::\n", i);
            employees[i] = Employee.readEmployee();
        }
        System.out.println("STUDENT DETAILS: ");
        System.out.printf("%-20s|  %-20s|  %s\n", "USN", "NAME", "ADDRESS");
        printAll(students);
        System.out.println("---------------------------------------------");
        System.out.println("EMPLOYEES DETAILS: ");
        System.out.printf("%-20s|  %-20s|  %s\n", "EMPL ID", "NAME", "ADDRESS");
        printAll(employees);
        System.out.println("---------------------------------------------");
        System.out.println("COLLEGES DETAILS: ");
        System.out.printf("%-20s|  %s\n", "NAME", "ADDRESS");
        printAll(colleges);
        System.out.println("---------------------------------------------");
    }
}
