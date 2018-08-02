plugins {
    application
}

application {
    mainClassName = "section01.task76.RegisterConverter"
}

val run by tasks.getting(JavaExec::class) {
    standardInput = System.`in`
}
