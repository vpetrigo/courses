There is a `class Request(data: String)` for representing some XML requests in a
payment system. The class has a getter method `getData()` and a constructor with
one argument (`data`). See below.

Typically, the value of data looks like shown below (in a human-readable format,
in processing it's a single line string).

```xml
<request>
  <transaction>
    <type>payment</type>
    <sum>100000</sum>
    <order_id>e94dc619-6172-4ffe-aae8-63112c551570</order>
    <desc>We'd like to buy an elephant</desc>
  </transaction>
  <digest>CZVMYTgc3iiOdJjFP+6dhQ==</digest>
</request>
```

You should to write the chain of responsibility pattern in functional style for
stage-by-stage request creating.

For this:

1) write a functional interface `RequestHandler` with a single abstract method
handle and a default method; the first is needed for using lambda expressions
and should accept a `Request` and returns new `Request` with changed data, the
second is for combining several handlers into the one.

2) create a `commonRequestHandler` combined from three existing handlers:
`wrapInTransactionTag`, `createDigest` and `wrapInRequestTag`.

**Important.** Use the provided template for your solution. Do not change it and
read comments in the code. The template is long enough, scroll it to the bottom.
All comments where your code is expected start with !!!

In the next step, you can read how the requests should be created. Keep in mind,
all handlers with logic are already implemented and available for you. You need to
write only a suitable functional interface and compose all existing handlers as
functions into one `commonRequestHandler` to follow the described algorithm.
