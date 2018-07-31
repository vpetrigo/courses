package section01.task04;

import java.util.Scanner;

public class Biker {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        int velocity = reader.nextInt();
        int time = reader.nextInt();
        int mkad_length = 109;
        int path = velocity * time % mkad_length;
        int stop = (mkad_length + path) % mkad_length;

        System.out.println(stop);
    }
}
