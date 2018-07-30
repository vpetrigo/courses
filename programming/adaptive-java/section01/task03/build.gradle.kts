plugins {
    application
}

application {
    mainClassName = "section01.task03.Snail"
    applicationDefaultJvmArgs = listOf("-ea")
}

val run by tasks.getting(JavaExec::class) {
    standardInput = System.`in`
}
