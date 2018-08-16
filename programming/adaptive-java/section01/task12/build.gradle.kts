plugins {
    application
}

application {
    mainClassName = "section01.task12.Main"
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}