plugins {
    application
}

application {
    mainClassName = "section01.task40.Main"
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}
