plugins {
    application
}

application {
    mainClassName = "section01.task129.Main"
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}
