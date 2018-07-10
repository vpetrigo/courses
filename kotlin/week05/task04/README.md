## Html builder

1. Fill the table with the proper values from the product list.

```kotlin
data class Product(val description: String, val price: Double, val popularity: Int)
```

2. Color the table like a chess board (using getTitleColor() and getCellColor() functions above). Pass a color as an argument to the functions tr, td.

```kotlin
open class Tag(val name: String)

class Attribute(val name : String, val value : String)

fun <T: Tag> T.set(name: String, value: String?): T

fun <T: Tag> Tag.doInit(tag: T, init: T.() -> Unit): T

class Html: Tag("html")
class Table: Tag("table")
class Center: Tag("center")
class TR: Tag("tr")
class TD: Tag("td")
class Text(val text: String): Tag("b")

fun html(init: Html.() -> Unit): Html

fun Html.table(init : Table.() -> Unit): Table
fun Html.center(init : Center.() -> Unit): Center

fun Table.tr(color: String? = null, init : TR.() -> Unit): TR

fun TR.td(color: String? = null, align : String = "left", init : TD.() -> Unit): TD

fun Tag.text(s : Any?): Text
```
