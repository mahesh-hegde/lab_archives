package Program4.RVCE;

import Program4.CSE.ThirdSem;

public class CSEDept extends ThirdSem {
    public void welcome() {
        // super.welcome();  // can use superclass method, it's public
        System.out.println("Welcome to CSEDept, Young Budding Engineers    -- CSEDept");
    }
    private void printStat() {
        // super.printStat()   // cannot access this, it's private
        System.out.println("70 Students in class      -- CSEDept");
    }
    protected void printBuildingNum() {
        System.out.println("Building Num: 4    -- CSEDept");
    }
    void printTopperName() {
        // super.printTopperName()  // cannot access this, it's package scoped
        System.out.println("Topper is Mohanlal    -- CSEDept");
    }
    public static void main(String[] args) {
        CSEDept dept = new CSEDept();

        System.out.println("Testing instance methods: ");
        dept.welcome();
        dept.printStat();
        dept.printBuildingNum();
        dept.printTopperName();

        System.out.println("\nTesting subtype polymorphism");
        ThirdSem.welcomeOf(dept);
        ThirdSem.printStatOf(dept);
        ThirdSem.printBuildingNumOf(dept);
        ThirdSem.printTopperNameOf(dept);
    }
}
