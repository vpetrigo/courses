package section01.task03;

import java.util.Scanner;

public class Snail {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        int height = reader.nextInt();
        int speedUp = reader.nextInt();
        int speedDown = reader.nextInt();
        assert height > 0;
        assert speedUp > speedDown;
        int step = speedUp - speedDown;
        int days = 1 + (height - speedUp) / step + ((height - speedUp) % step + step - 1) / step;

        System.out.println(days);
    }
}
