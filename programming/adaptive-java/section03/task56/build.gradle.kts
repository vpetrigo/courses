plugins {
    application
}

application {
    mainClassName = "section03.task56.ProductCollector"
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
