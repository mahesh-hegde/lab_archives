package Program4.CSE;

public class ThirdSem {
    public void welcome() {
        System.out.print("Welcome to 3rd sem - young useless engineers");
        System.out.println("    -- ThirdSem");

    }
    private void printStat() {
        System.out.println("70 students in the class    -- ThirdSem");
    }
    protected void printBuildingNum() {
        System.out.println("Building No. 4    -- ThirdSem");
    }
    void printTopperName() {
        System.out.println("Topper of this class is Rajanikanth    -- ThirdSem");
    }
    // demonstrate how subtyping works wrt private methods
    public static void printStatOf(ThirdSem t) {
        t.printStat();
    }
    public static void printBuildingNumOf(ThirdSem t) {
        t.printBuildingNum();
    }
    public static void printTopperNameOf(ThirdSem t) {
        t.printTopperName();
    }
    public static void welcomeOf(ThirdSem t) {
        t.welcome();
    }
}
