val month = "(JAN|FEB|MAR|APR|MAY|JUN|JUL|AUG|SEP|OCT|NOV|DEC)"

fun getPattern(): String = """\d{2} $month \d{4}"""

fun main(args: Array<String>) {
    var str1 = "13 JUN 1992"
    var str2 = "13.06.1992"
    var dateRegEx = Regex(getPattern())

    println("Does $str1 match: ${dateRegEx.matches(str1)}")
    println("Does $str2 match: ${dateRegEx.matches(str2)}")
}