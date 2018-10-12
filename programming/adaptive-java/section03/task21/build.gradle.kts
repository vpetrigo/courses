plugins {
    application
}

java {
    sourceCompatibility = JavaVersion.VERSION_1_8
    targetCompatibility = JavaVersion.VERSION_1_8
}

application {
    mainClassName = "section03.task21.JProcessor"
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}
