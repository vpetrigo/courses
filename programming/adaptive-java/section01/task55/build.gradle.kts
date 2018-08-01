plugins {
    application
}

application {
    mainClassName = "section01.task55.Genome"
}

val run by tasks.getting(JavaExec::class) {
    standardInput = System.`in`
}
