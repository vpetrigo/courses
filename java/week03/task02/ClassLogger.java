/**
 * Реализуйте метод, позволяющий другим методам узнать, откуда их вызвали.
 * Метод getCallerClassAndMethodName() должен возвращать имя класса 
 * и метода, откуда вызван метод, вызвавший данный утилитный метод.
 * Или null (нулевую ссылку, а не строку "null"), если метод,
 * вызвавший getCallerClassAndMethodName() является точкой 
 * входа в программу, т.е. его никто не вызывал.
 * 
 * Это актуально, например, в библиотеках логирования, 
 * где для каждого сообщения в логе надо выводить класс и 
 * метод, откуда сообщение было залогировано.
 */
public class ClassLogger {
    public static String getCallerClassAndMethodName() {
        StackTraceElement[] st = new Throwable().getStackTrace();
        
        if (st.length > 2) {
            return new String(st[2].getClassName() + "#" + st[2].getMethodName());
        }

        return null;
    }

    public static void main(String... args) {
        System.out.println(getCallerClassAndMethodName());
        anotherMethod();
    }

    public static void anotherMethod() {
        System.out.println(getCallerClassAndMethodName());
    }
}