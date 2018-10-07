package section03.task89;

import org.jetbrains.annotations.NotNull;

import java.io.Serializable;

class MyInt implements Serializable, Cloneable, Comparable<Integer> {
    @Override
    public int compareTo(@NotNull Integer o) {
        return 0;
    }
}
