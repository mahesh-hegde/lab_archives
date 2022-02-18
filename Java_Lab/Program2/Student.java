package Program2;

import java.util.Scanner;

public class Student {
    public final String USN, name;
    public final Address address;
    public Student(String USN, String name, Address address) {
        this.USN = USN;
        this.name = name;
        this.address = address;
    }
    public static Student readStudent() {
        Scanner in = new Scanner(System.in);
        System.out.print("USN: ");
        String usn = in.nextLine();
        System.out.print("Name: ");
        String name = in.nextLine();
        System.out.print("Address :: \n");
        Address address = Address.readAddress();
        return new Student(usn, name, address); // constructor
    }

    public String toString() {
        return String.format("%-20s|  %-20s|  %s\n", USN, name,
                address.toString());
    }
}
