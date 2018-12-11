package section01.task194;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

class Main {
    private static List<List<Integer>> outputDecompositions;

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        int inputNum = reader.nextInt();
        outputDecompositions = new ArrayList<>();

        decomposition(inputNum, new ArrayList<>());
        outputDecompositions.sort((o1, o2) -> {
            for (int i = 0; i < Integer.min(o1.size(), o2.size()); ++i) {
                int c = o1.get(i).compareTo(o2.get(i));

                if (c != 0) {
                    return c;
                }
            }

            return Integer.compare(o1.size(), o2.size());
        });
        outputDecompositions.forEach(list -> System.out.println(
                list.stream().map(String::valueOf)
                    .collect(Collectors.joining(" "))));
    }

    public static void decomposition(int num, List<Integer> decompositionList) {
        if (num == 0) {
            Collections.reverse(decompositionList);
            outputDecompositions.add(decompositionList);
        }
        else {
            if (decompositionList.isEmpty() ||
                num >= decompositionList.get(decompositionList.size() - 1)) {
                int leftBorder = Integer.max(1, !decompositionList.isEmpty() ?
                                                decompositionList
                                                        .get(decompositionList
                                                                     .size() -
                                                             1) : 0);

                for (int i = leftBorder; i < num + 1; ++i) {
                    List<Integer> temporary =
                            new ArrayList<>(decompositionList);

                    temporary.add(i);
                    decomposition(num - i, temporary);
                }
            }
        }
    }
}
