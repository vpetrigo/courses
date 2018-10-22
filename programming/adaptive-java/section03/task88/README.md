Pie company is looking for talanted baker and you are invited to implement one.
The baker's duty is to get orders for bakery and it's varieties and produce it.
Class definition and method's backbone follows:

```java
class Paper {}

class Bakery {}

class Cake extends Bakery {}

class ReflexiveBaker {
  
  /**
   * Create bakery of the provided class.
   * 
   * @param order class of bakery to create
   * @return bakery object
   */
  public Object bake(Class order) {
    // Add implementation here
  }
  
}
```

The task is to redesign method signature types if needed and to add
implementation. The bake method should conform to the following:

- Create objects of class Bakery or any subclass of it according to class 
argument
- Flag compile-time error if order argument is not Bakery or any subclass of 
it (e.g. if it is Paper or Object)
- ﻿It's guaranteed that all subclasses of Bakery will have public 
parameterless constructor.

### Sample Input:

```java
ReflexiveBaker class
```

### Sample Output:

```
Well done!
```
