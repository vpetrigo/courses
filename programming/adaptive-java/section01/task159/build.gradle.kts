plugins {
    application
}

application {
    mainClassName = "section01.task159.Main"
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}
