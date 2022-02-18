package Program2;
import java.util.Scanner;

public class Address {
    public final int street_num;
    public final String city, state, country;
    public Address(int street_num, String city, String state, String country) {
        this.street_num = street_num;
        this.city = city;
        this.state = state;
        this.country = country;
    }

    public static Address readAddress() {
        Scanner in = new Scanner(System.in);
        System.out.print("  Street Num: ");
        int street_num = in.nextInt();
        in.nextLine();
        System.out.print("  City: ");
        String city = in.nextLine();
        System.out.print("  State: ");
        String state = in.nextLine();
        System.out.print("  Country: ");
        String country = in.nextLine();
        return new Address(street_num, city, state, country);
    }

    public String toString() {
        return String.format("%d, %s, %s, %s", street_num, city, state, country);
    }
}
