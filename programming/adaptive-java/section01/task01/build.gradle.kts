plugins {
    application
}

application {
    mainClassName = "section01.task01.Main"
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}