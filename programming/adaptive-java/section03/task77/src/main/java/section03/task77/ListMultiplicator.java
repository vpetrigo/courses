package section03.task77;

import java.util.Collection;
import java.util.List;

public class ListMultiplicator {
    /**
     Multiplies original list provided numper of times

     @param list list to multiply
     @param n times to multiply, should be zero or greater
     */
    public static void multiply(List<?> list, int n) {
        // Add implementation here
        // Add implementation here
        if (n <= 0) {
            list.clear();
        }

        @SuppressWarnings("unchecked")
        List<Object> objectList = (List<Object>)list;

        int upperBound = list.size();

        for (int i = 0; i < n - 1; ++i)
        {
            objectList.addAll(list.subList(0, upperBound));
        }
    }
}
