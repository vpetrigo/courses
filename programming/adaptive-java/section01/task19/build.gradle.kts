plugins {
    application
}

application {
    mainClassName = "section01.task19.Main"
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}
