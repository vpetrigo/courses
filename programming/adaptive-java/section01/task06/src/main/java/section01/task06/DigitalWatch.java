package section01.task06;

import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;

public class DigitalWatch {
    public static void main(String[] args) {
        int seconds = new Scanner(System.in).nextInt();

        System.out.println(LocalTime.MIN.plusSeconds(seconds).format(DateTimeFormatter.ofPattern("H:mm:ss")));
    }
}
