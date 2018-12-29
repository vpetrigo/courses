package section01.task62;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UncheckedIOException;
import java.util.Arrays;
import java.util.function.Supplier;

public class Main {
    public static void main(String[] args) {
        BufferedReader reader =
                new BufferedReader(new InputStreamReader(System.in));
        Supplier<int[]> supplier = () -> {
            try {
                return reader.readLine().toLowerCase().chars().sorted()
                             .toArray();
            } catch (IOException e) {
                throw new UncheckedIOException(e);
            }
        };
        System.out.println(
                Arrays.equals(supplier.get(), supplier.get()) ? "True" :
                "False");
    }
}
