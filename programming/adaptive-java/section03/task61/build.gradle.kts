plugins {
    application
}

application {
    mainClassName = "section03.task61.PrimeNumbersCounter"
}

dependencies {
    testImplementation("org.junit.jupiter:junit-jupiter-api:5.2.0")
    testRuntimeOnly("org.junit.jupiter:junit-jupiter-engine:5.2.0")
}

tasks.withType<Test> {
    useJUnitPlatform()
}
