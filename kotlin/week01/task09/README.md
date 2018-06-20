## Smart casts

Rewrite the following Java code using [smart casts][1] and [when][2] expression:

```java
public int eval(Expr expr) {
    if (expr instanceof Num) {
        return ((Num) expr).getValue();
    }
    if (expr instanceof Sum) {
        Sum sum = (Sum) expr;
        return eval(sum.getLeft()) + eval(sum.getRight());
    }
    throw new IllegalArgumentException("Unknown expression");
}
```

[1]: https://kotlinlang.org/docs/reference/typecasts.html#smart-casts
[2]: https://kotlinlang.org/docs/reference/control-flow.html#when-expression
