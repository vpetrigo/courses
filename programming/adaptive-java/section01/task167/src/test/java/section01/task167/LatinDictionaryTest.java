package section01.task167;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;

import java.util.*;

public class LatinDictionaryTest {
    @Test
    void testDictionary() {
        Map<String, List<String>> dictOne = new HashMap<>();
        Map<String, List<String>> expect = new HashMap<>();
        List<String> expOne = Arrays.asList("apple");
        List<String> expTwo = Arrays.asList("fruit");

        expect.put("baca", expTwo);
        expect.put("bacca", expTwo);
        expect.put("popum", expTwo);
        expect.put("malum", expOne);

        List<String> listOne = Arrays.asList("malum");
        List<String> listTwo = Arrays.asList("baca", "bacca", "popum");

        dictOne.put("fruit", listTwo);
        dictOne.put("apple", listOne);
        Assertions.assertEquals(expect, LatinDictionary.getLatinDictionary(dictOne));
    }

    @Test
    void testDictionaryOrder() {
        List<String> expectedList = new ArrayList<>();

        expectedList.add("apple");
        expectedList.add("banana");

        Map<String, List<String>> dict = new HashMap<>();
        List<String> list = new ArrayList<>();

        list.add("mamula");
        dict.put("banana", list);
        dict.put("apple", list);

        Map<String, List<String>> result = LatinDictionary.getLatinDictionary(dict);

        Assertions.assertIterableEquals(expectedList, result.get("mamula"));
    }
}
