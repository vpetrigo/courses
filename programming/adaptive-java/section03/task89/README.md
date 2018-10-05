You need to implement method `getComparatorType(Class)` in `ComparatorInspector`
class. The method should examine provided class and return [`Type`][1] object
 that
corresponds to the type parameter that parameterizes `Comparable` interface the
class implements. Consider the example:

```java
class MyInt implements Comparable<Integer> {
    // Implementation omitted 
}

// Method to implement
Type type = ComparatorInspector.getComparatorType(MyInt.class);

System.out.println(type.getTypeName());
// prints: java.lang.Integer since MyInt implements Comparable with Integer parameter type
```

The method should:

- Return type parameter for `Comparable` interface class implements
- Return `null` if `Comparable` interface does not have type parameter
- Should not produce compile-time warnings

Additional requirements:﻿

- Compile-time error should arise if class not implementing Comparable is 
provided as input value
- No 'rawtype' warnings should remain or be supressed
- Method `getComparatorType` should be generic

You are free to correct method's type signature if needed.

[1]: https://docs.oracle.com/javase/8/docs/api/java/lang/reflect/Type.html