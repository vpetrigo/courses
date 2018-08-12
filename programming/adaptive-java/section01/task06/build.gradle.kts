plugins {
    application
}

application {
    mainClassName = "section01.task06.DigitalWatch"
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}