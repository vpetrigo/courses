public final class ComplexNumber {
    private final double re;
    private final double im;

    public ComplexNumber(double re, double im) {
        this.re = re;
        this.im = im;
    }

    public double getRe() {
        return re;
    }

    public double getIm() {
        return im;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
          return true;
        }

        if (o instanceof ComplexNumber) {
            ComplexNumber c = (ComplexNumber) o;
            return (re == c.re && im == c.im);
        }
        return false;
    }

    @Override
    public int hashCode() {
        return Double.hashCode(re + im);
    }

    public static void main(String[] args) {
        ComplexNumber a = new ComplexNumber(1, 2);
        ComplexNumber b = new ComplexNumber(1, 2);
        ComplexNumber c = new ComplexNumber(3, 4);
        System.out.println(a.hashCode());
        System.out.println(b.hashCode());
        System.out.println(c.hashCode());
        System.out.println(a.equals(b));
        System.out.println(a.equals(c));
    }
}