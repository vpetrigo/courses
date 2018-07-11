package section03.task37;

import java.util.function.Consumer;

public class ToUpperStringLambda {
    interface SevenArgs {
        String run(String a, String b, String c, String d, String e, String f, String g);
    }

    public static String processString(String in, SevenArgs strRunner) {
        String[] arr = in.split("\\s+");

        return strRunner.run(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]);
    }

    public static void main(String[] args) {
        String test = new String("The lambda has too many string arguments.");

        System.out.println(processString(test, 
        (a, b, c, d, e, f, g) -> new StringBuilder().append(a.toUpperCase())
                                                    .append(b.toUpperCase())
                                                    .append(c.toUpperCase())
                                                    .append(d.toUpperCase())
                                                    .append(e.toUpperCase())
                                                    .append(f.toUpperCase())
                                                    .append(g.toUpperCase())
                                                    .toString()));
    }
}
