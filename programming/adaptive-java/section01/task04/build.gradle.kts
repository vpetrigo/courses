plugins {
    application
}

application {
    mainClassName = "section01.task04.Biker"
}

val run by tasks.getting(JavaExec::class) {
    standardInput = System.`in`
}

