public class GregorianCalendar {
    public static int leapYearCount(int year) {
        return (year / 4) - (year / 100) + (year / 400);
    }

    public static void main(String[] args) {
        assert leapYearCount(1) == 0;
        assert leapYearCount(100) == 24;
        assert leapYearCount(4) == 1;
    }
}
