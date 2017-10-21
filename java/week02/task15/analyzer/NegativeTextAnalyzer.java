package analyzer;

import analyzer.KeywordAnalyzer;

public class NegativeTextAnalyzer extends KeywordAnalyzer implements TextAnalyzer {
    private static String[] negative = {":(", "=(", ":|"};

    public NegativeTextAnalyzer() {}

    @Override
    protected Label getLabel() {
        return Label.NEGATIVE_TEXT;
    }

    @Override
    protected String[] getKeywords() {
        return negative;
    }
}