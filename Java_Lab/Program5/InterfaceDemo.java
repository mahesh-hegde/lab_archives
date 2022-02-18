package Program5;

import static java.lang.Thread.sleep;

interface Animal {
    public void eat();
    public void sound();
}

interface TiredAnimal extends Animal {
    public void takeRest();
}

class Lion implements TiredAnimal {
    int weight;
    int height;
    public Lion(int height, int weight) {
        this.weight = weight;
        this.height = height;
    }
    public String toString() {
        return "A Lion with weight " + weight + "KG and height " + height
                + "cm";
    }
    public void eat() {
        System.out.println("HUNTING: " + toString());
    }
    public void sound() {
        System.out.println("ROARING: " + toString());
    }
    public void takeRest() {
        System.out.println("A " + this.toString() + " is sleeping");
    }
}

class Snake implements Animal {
    int length, weight;
    public Snake(int length, int weight) {
        this.weight = weight;
        this.length = length;
    }
    public String toString() {
        return "A Snake with weight " + weight + "KG and length " + length
                + "cm";
    }
    public void eat() {
        System.out.println("INSECT SEARCH: " + toString());
    }
    public void sound() {
        System.out.println("HISSING: " + toString());
    }
}

public class InterfaceDemo {
    static void demoAnimal(Animal animal) {
        System.out.println("Argument type " + animal.getClass().toString());
        System.out.print("eat(): ");
        animal.eat();
        System.out.print("sound(): ");
        animal.sound();
    }
    static void demoTiredAnimal(TiredAnimal animal) {
        demoAnimal(animal);
        System.out.print("takeRest(): ");
        animal.takeRest();
        System.out.println();
    }
    static int randomInt(int min, int limit) {
        int range = limit - min;
        return (int)(Math.random() * range) + min;
    }
    public static void main(String[] args) {
        var snake = new Snake(randomInt(40,500),
                randomInt(10, 30));
        var lion = new Lion(randomInt(80, 120),
                randomInt(40, 80));
        demoTiredAnimal(lion);
        demoAnimal(snake);
    }
}
