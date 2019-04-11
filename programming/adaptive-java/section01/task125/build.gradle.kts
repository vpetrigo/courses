plugins {
    application
}

application {
    mainClassName = "section01.task125.Main"
}

java {
    sourceCompatibility = JavaVersion.VERSION_1_8
    targetCompatibility = JavaVersion.VERSION_1_8
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}
