package Program7;

import java.util.*;

import static java.lang.Thread.sleep;

class Market {
    private ArrayList<String> fruits = new ArrayList<>();
    private int fruitsNumber;

    public Market(int fruitsNumber) {
        if (fruitsNumber <= 0)
            throw new IllegalArgumentException("Negative No.");
        this.fruitsNumber = fruitsNumber;
    }

    private synchronized boolean isFull() {
        return fruits.size() == this.fruitsNumber;
    }
    private synchronized boolean isEmpty() {
        return fruits.isEmpty();
    }
    // consumer & producer
    public synchronized void farmer(String fruit) {
        while (isFull()) {
            // System.out.println("Market Full!!");
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println("Interrupted");
            }
        }
        fruits.add(fruit);
        System.out.println("Added " + fruit);
        notify();
    }
    public synchronized String consumer() {
        while  (isEmpty()) {
            // System.out.println("Market Empty!!");
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println("Interrupted");
            }
        }
        String boughtFruit = fruits.remove(0);
        notifyAll();
        System.out.println("Got " + boughtFruit);
        return boughtFruit;
    }
}

public class Main {
    static String[] fruits = {"Orange", "Mango", "Banana", "Watermelon", "Tomato"};
    static Random r = new Random();
    static int randomFruit() {
        return r.nextInt(fruits.length);
    }
    static Thread createConsumer(Market m) {
        return new Thread() {
            @Override
            public void run() {
                System.out.println("Consumer Thread Created");
                String fruitName = m.consumer();
            }
        };
    }
    static Thread createProducer(Market m) {
        return new Thread() {
            @Override
            public void run() {
                System.out.println("Farmer Thread Created");
                String fruitName = fruits[randomFruit()];
                m.farmer(fruitName);
            }
        };
    }
    public static void main(String[] args) {
        Market market = new Market(16);
        while(true) {
            if (r.nextBoolean()) {
                createProducer(market).start();
            } else {
                createConsumer(market).start();
            }
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {}
        }
    }
}