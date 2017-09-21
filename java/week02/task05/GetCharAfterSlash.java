public class GetCharAfterSlash {
    /**
     * Return unicode char after '\' in <code>pos</code>
     * 
     * @param pos position of char after '\'
     * @return the unicode character in <code>pos</code>
     */
    public static char charExpression(int pos) {
        return (char) ('\\' + pos);
    }

    public static void test() {
        assert charExpression(32) == '|';
        assert charExpression(29) == 'y';
    }

    public static void main(String[] args) {
        test();
    }
}
