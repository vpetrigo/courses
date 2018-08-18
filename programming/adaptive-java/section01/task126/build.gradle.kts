plugins {
    application
}

application {
    mainClassName = "section01.task126.Main"
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}