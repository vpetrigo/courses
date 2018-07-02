## Lazy property

Add a custom getter to make the 'lazy' `val`
really lazy. It should be initialized by the
invocation of `initializer()` at the moment of the first access.

You can add as many additional [properties][1] as you need.

Do not use [delegated properties][2]!

[1]: https://kotlinlang.org/docs/reference/properties.html
[2]: https://kotlinlang.org/docs/reference/delegated-properties.html
