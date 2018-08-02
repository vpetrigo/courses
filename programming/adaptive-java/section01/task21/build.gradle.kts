plugins {
    application
}

application {
    mainClassName = "section01.task21.Malevia"
}

val run by tasks.getting(JavaExec::class) {
    standardInput = System.`in`
}
