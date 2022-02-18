package Program3;

import java.util.Scanner;

enum Color { Red, Blue, Green, White, Black, Orange }

class Circle {
    protected double radius;
    protected Color color;

    public Circle(double radius, Color color) {
        this.radius = radius;
        this.color = color;
    }

    public Circle(double radius) {
        this(radius, Color.White);
    }

    public double getRadius() {
        return this.radius;
    }

    public Color getColor() {
        return color;
    }

    public double getArea() {
        return Math.PI * radius * radius;
    }
}

class Cylinder extends Circle {
    double height;
    public Cylinder(double radius, double height, Color color) {
        super(radius, color);
        this.height = height;
    }

    public Cylinder(double radius, double height) {
        super(radius);
        this.height = height;
    }

    public double getHeight() {
        return height;
    }

    @Override
    public double getArea() {
        return (super.getArea()) * 2 + (2 * Math.PI * getRadius() * height);
    }

    public double getVolume() {
        return super.getArea() * height;
    }

    static boolean doubleEq(double a, double b) {
        return Math.abs(a - b) < 0.0001;
    }

    public boolean equals(Cylinder other) {
        return (doubleEq(getVolume(),other.getVolume())
                && doubleEq(getArea(), other.getArea())
            && getColor() == other.getColor());
    }

    public String toString() {
        return String.format(
                "Radius: %g\nHeight: %g\nSurfaceArea: %g\nVolume: %g\nColor: %s\n",
                getRadius(),
                getHeight(),
                getArea(),
                getVolume(),
                getColor().toString()
        );
    }
}

public class InheritanceDemo {
    public static Cylinder readCylinder() {
        Scanner in = new Scanner(System.in);
        System.out.print("Radius: ");
        double r = in.nextDouble();
        System.out.print("Height: ");
        double h = in.nextDouble();
        System.out.print("Color: ");
        String color = in.next();
        try {
            return new Cylinder(r, h, Color.valueOf(color));
        } catch (IllegalArgumentException e) {
            System.out.println("Invalid Color, Assigning default (White) ");
            return new Cylinder(r, h);
        }
    }

    public static void main(String[] args) {
        System.out.println("Cylinder 1: ");
        Cylinder a = readCylinder();
        System.out.println("Cylinder 2: ");
        Cylinder b = readCylinder();
        System.out.println("----------------------------------------------");
        if (a.equals(b)) {
            System.out.println("Both Cylinders are EQUAL. Data:\n" + a.toString());
        } else {
            System.out.println("Cylinder 1: ");
            System.out.print(a.toString());
            System.out.println("----------------------------------------------");
            System.out.println("Cylinder 2: ");
            System.out.print(b.toString());
        }
    }
}
