plugins {
    application
}

application {
    mainClassName = "section01.task26.Main"
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}