plugins {
    application
}

application {
    mainClassName = "section01.task123.MatrixMax"
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}
