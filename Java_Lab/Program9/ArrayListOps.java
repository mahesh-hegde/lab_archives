package Program9;

import java.util.*;

public class ArrayListOps {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.println("Enter array elements");
        String[] words = in.nextLine().split("[ ]+");
        System.out.println("Read Array: " + Arrays.toString(words));

        assert words.length > 2;

        var list = Arrays.asList(words);
        System.out.printf("List = %s\n", list);

        System.out.println("i) copy list contents to an arraylist");
        ArrayList<String> alist = new ArrayList<>(list);
        System.out.printf("ArrayList: %s = %s\n", alist.getClass(), alist);

        System.out.println("\nii) Copy arraylist contents to array");
        String[] array = new String[alist.size()];
        array = alist.toArray(array);
        System.out.printf("Array after copying from arraylist = %s\n", Arrays.toString(array));

        System.out.println("\niii) reverse arraylist content");
        var reversedList = new ArrayList<>(alist);
        Collections.reverse(reversedList);
        System.out.printf("Reversed list = %s\n", reversedList);

        System.out.println("\niv) get a sublist from arraylist");
        var sublist = alist.subList(0, alist.size()/2);
        System.out.printf("Half of arraylist: %s = %s\n", sublist.getClass(), sublist);

        System.out.println("\nv) sort the array list");
        Collections.sort(alist);
        System.out.printf("sorted array list = %s\n", alist);

        System.out.println("\nvi) clone array list");
        var copy = new ArrayList<String>(alist);
        System.out.printf("copy = %s\n", copy);
    }
}
