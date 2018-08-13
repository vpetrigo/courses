plugins {
    application
}

application {
    mainClassName = "section01.task39.Main"
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}
