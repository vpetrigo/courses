## Data classes

Rewrite the following Java code to Kotlin:

```java
public class Person {
    private final String name;
    private final int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }
}
```

Then add an annotation `data` to the resulting class. This
annotation means the compiler will generate a bunch of useful
methods in this class: `equals`/`hashCode`, `toString` and some others.
The `getPeople` function should start to compile.

Read about [classes][1], [properties][2] and [data classes][3].

[1]: https://kotlinlang.org/docs/reference/classes.html
[2]: https://kotlinlang.org/docs/reference/properties.html
[3]: https://kotlinlang.org/docs/reference/data-classes.html