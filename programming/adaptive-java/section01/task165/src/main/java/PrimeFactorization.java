package section01.task165;

import java.util.List;
import java.util.ArrayList;
import java.util.Scanner;

class PrimeFactorization {
    public static List<Integer> factorize(int number) {
        ArrayList<Integer> primeFact = new ArrayList<>();
        int prime = 2;

        while (prime * prime <= number) {
            while (number % prime == 0) {
                primeFact.add(prime);
                number /= prime;
            }
  
            prime += 1;
        }
  
        if (number > prime) {
            primeFact.add(number);
        }

        return primeFact;
    }

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        int value = reader.nextInt();
        
        List<Integer> primeFact = factorize(value);
        primeFact.forEach(v -> System.out.printf("%d ", v));
    }
}