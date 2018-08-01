package section01.task55;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Genome {
    public static void main(String[] args) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String line = reader.readLine();
            long nGC = line.toLowerCase().chars().filter(c -> c == 'g' || c == 'c').count();

            System.out.println((double)nGC / line.length() * 100);
        }
        catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
