package analyzer;

public abstract class KeywordAnalyzer {
    protected abstract String[] getKeywords();

    protected abstract Label getLabel();

    public Label processText(String text) {
        for (String k : getKeywords()) {
            if (text.toLowerCase().contains(k.toLowerCase())) {
                return getLabel();
            }
        }

        return Label.OK;
    }
}