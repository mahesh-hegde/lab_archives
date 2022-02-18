package Program2;

import java.util.Scanner;

public class College {
    public final String name;
    public final Address address;
    public College(String name, Address address) {
        this.name = name;
        this.address = address;
    }
    public String toString() {
        return String.format("%-20s|  %s\n", name, address.toString());
    }
    public static College readCollege() {
        Scanner in = new Scanner(System.in);
        System.out.print("Name: ");
        String name = in.nextLine();
        System.out.print("Address :: \n");
        Address address = Address.readAddress();
        return new College(name, address); // constructor call
    }
}
