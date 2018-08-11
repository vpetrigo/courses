plugins {
    application
}

application {
    mainClassName = "section01.task154.RomanNumbers"
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}
