plugins {
    application
}

application {
    mainClassName = "section01.task140.Main"
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}