package Program6;

import java.util.Scanner;

enum CurrencyType { OLD, NEW }

class DemonetizationException extends Exception {
    int amt;
    public DemonetizationException(int amt) {
        this.amt = amt;
    }
    @Override
    public String getMessage() {
        return String.format("Can't deposit Rs %,d, Max limit Rs. 5,000 for old currency",
                amt);
    }
}

class InsufficientBalanceException extends Exception {
    int req, cur;
    public InsufficientBalanceException(int req, int cur) {
        this.req = req;
        this.cur = cur;
    }
    @Override
    public String getMessage() {
        return String.format("Current Balance: Rs. %,d, Requires at least Rs. %,d",
                cur, req + 500);
    }
}

class Account {
    int balance = 500;
    public void deposit(int amount, CurrencyType type)
            throws DemonetizationException {
        if (amount < 0) {
            throw new IllegalArgumentException("Negative Amount Not Allowed");
        }
        if (type == CurrencyType.OLD && amount > 5000) {
            throw new DemonetizationException(amount);
        }
        balance += amount;
        System.out.println("New Balance: Rs. " + balance);
    }

    public int currBalance() {
        return balance;
    }

    public void withDraw(int amount) throws InsufficientBalanceException {
        if (amount < 0) {
            throw new IllegalArgumentException("Negative Amount Not Allowed");
        }
        if (balance - amount < 500) {
            throw new InsufficientBalanceException(amount, balance);
        }
        balance -= amount;
        System.out.println("New Balance: Rs. " + balance);
    }
}

public class Customer {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int amt;
        Account account = new Account();
        System.out.println("Account created with balance Rs. " + account.currBalance());
        while (true) {
            System.out.println("0. Exit  1. Deposit  2. Withdraw  3.  Show Balance");
            int choice = in.nextInt();
            switch (choice) {
                case 0:
                    System.exit(0);
                case 1:
                    System.out.print("Amount to Deposit: ");
                    amt = in.nextInt();
                    in.nextLine();
                    System.out.print("Currency type (Old or New): ");
                    CurrencyType type = CurrencyType.valueOf(in.nextLine()
                            .toUpperCase());

                    try {
                        account.deposit(amt, type);
                    } catch (DemonetizationException de) {
                        System.out.println("DemonetizationException: " + de.getMessage());
                    } catch (IllegalArgumentException e) {
                        System.out.println("Illegal Argument: " + e.getMessage());
                    }
                    break;
                case 2:
                    System.out.print("Amount to Withdraw: ");
                    amt = in.nextInt();
                    try {
                        account.withDraw(amt);
                    } catch (InsufficientBalanceException e) {
                        System.out.println("InsufficientBalanceException: "
                                + e.getMessage());
                    } catch (IllegalArgumentException e) {
                        System.out.println("Illegal Argument: " + e.getMessage());
                    }
                    break;
                case 3:
                    System.out.println("Balance: Rs. " + account.currBalance());
                    break;
                default:
                    System.out.println("Invalid option!!");
            }
        }
    }
}
