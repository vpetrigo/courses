plugins {
    application
}

application {
    mainClassName = "section01.task71.Replace"
}

java {
    targetCompatibility = JavaVersion.VERSION_1_8
    sourceCompatibility = JavaVersion.VERSION_1_8
}

dependencies {
    testImplementation("org.junit.jupiter:junit-jupiter-api:5.5.0")
    testImplementation("org.junit.jupiter:junit-jupiter-params:5.5.0")
    testRuntimeOnly("org.junit.jupiter:junit-jupiter-engine:5.5.0")
    testRuntimeOnly("org.junit.jupiter:junit-jupiter-params:5.5.0")
}

tasks.withType<Test> {
    useJUnitPlatform()
    testLogging {
        events("passed", "skipped", "failed")
    }
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}