package Program2;

import java.util.Scanner;

public class Employee {
    public final String empID, name;
    public final Address address;
    public Employee(String empID, String name, Address address) {
        this.empID = empID;
        this.name = name;
        this.address = address;
    }
    public String toString() {
        return String.format("%-20s|  %-20s\t|  %s\n", empID, name,
                address.toString());
    }
    public static Employee readEmployee() {
        Scanner in = new Scanner(System.in);
        System.out.print("ID: ");
        String id = in.nextLine();
        System.out.print("Name: ");
        String name = in.nextLine();
        System.out.print("Address :: \n");
        Address address = Address.readAddress();
        return new Employee(id, name, address); // constructor call
    }
}