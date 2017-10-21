import analyzer.*;

public class Main {
    public static void main(String[] args) {
        String text = "Normal";

        System.out.println(checkLabels(new TextAnalyzer[]{new NegativeTextAnalyzer(), new SpamAnalyzer(new String[]{"Suck"})}, text));
    }

    public static Label checkLabels(TextAnalyzer[] analyzers, String text) {
        for (TextAnalyzer analyzer : analyzers) {
            Label res = analyzer.processText(text);
            if (res != Label.OK) {
                return res;
            }
        }

        return Label.OK;
    }
}