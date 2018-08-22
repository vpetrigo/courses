plugins {
    application
}

application {
    mainClassName = "section01.task58.Palindrome"
}

dependencies {
    testImplementation("org.junit.jupiter:junit-jupiter-api:5.2.0")
    testRuntimeOnly("org.junit.jupiter:junit-jupiter-engine:5.2.0")
}

tasks {
    "test"(Test::class) {
        useJUnitPlatform()
    }
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}