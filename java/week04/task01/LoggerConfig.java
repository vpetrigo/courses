import java.util.logging.Logger;
import java.util.logging.XMLFormatter;
import java.util.logging.ConsoleHandler;
import java.util.logging.Handler;
import java.util.logging.Level;

public class LoggerConfig {
    private static void configureLogging() {
        Logger classA = Logger.getLogger("org.stepic.java.logging.ClassA");
        Logger classB = Logger.getLogger("org.stepic.java.logging.ClassB");
        classA.setLevel(Level.ALL);
        classB.setLevel(Level.WARNING);

        Logger top = Logger.getLogger("org.stepic.java");
        Handler console = new ConsoleHandler();
        console.setFormatter(new XMLFormatter());
        console.setLevel(Level.ALL);
        top.addHandler(console);
        top.setUseParentHandlers(false);
    }

    static public void main(String[] args) {
        configureLogging();

        Logger testA = Logger.getLogger("org.stepic.java.logging.ClassA");

        testA.log(Level.INFO, "Hello");
    }
}